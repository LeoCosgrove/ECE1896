#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

std::vector<char> getHeader(std::string filepath){
	std::ifstream in(filepath, std::ios::binary);
  	if(in.fail()){
    	std::cout << "Could not open " << filepath << std::endl;
    	return std::vector<char>();
  	}
  	
  	std::vector<char> header;
  	header.resize(44);
  	
  	in.seekg(0);
  	in.read(header.data(), 44);
  	
  	in.close();
  	return header;
}

std::vector<short> getSamples(std::string filepath){
  	std::ifstream in(filepath, std::ios::binary);
  	if(in.fail()){
    	std::cout << "Could not open " << filepath << std::endl;
    	return std::vector<short>();
  	}

  	in.seekg(40); //go to byte 40-43 to read size
  	unsigned int size;
  	in.read((char*)&size, 4);

  	std::cout << "Audio bytes: " << size << std::endl;

  	in.seekg(34); //go to byte 34-35 to read bytes per sample
  	unsigned short bytes_per_sample;
  	in.read((char*)&bytes_per_sample, 2);
  	bytes_per_sample /= 8;

 	std::cout << "Bits per sample: " << bytes_per_sample*8 << std::endl;
 	std::cout << "Number of samples: " << size / bytes_per_sample << std::endl;

  	//Seek to beginning of data on byte 44
  	in.seekg(44);

  	std::vector<short> samples;
  	samples.resize(size/bytes_per_sample);

  	//read all the data
  	in.read((char*)samples.data(), size);
  	//for(unsigned int i = 0; i < size/bytes_per_sample; i++){
  	//  in.read(&samples.data()[i], 2);
  	//}

  	in.close();
  	return samples;
}

void writeSamples(std::vector<char> header, std::vector<short> samples, std::string filepath){
  	std::ofstream out(filepath, std::ios::binary);

  	out.write(header.data(), 44);
  	out.write((char*)samples.data(), samples.size()*2);

  	out.close();
}

float root_mean_square(std::vector<short>& samples){
	float rms = 0;
	for(int i = 0; i < samples.size(); i++){
		float s = samples[i];
		rms += std::pow(s, 2);
	}
	rms = std::sqrt(rms / (float)samples.size());
	return rms / (float)0xFFFF;
}

//Uses a running total instead of slices (n^2 complexity!)
//Not suitable for real time DSP unfortunately
/*
void adjust_volume_running(float volume, std::vector<short>& samples){
	const int samples_per_slice = 100;

	//Calculate rms and adjust volume over a slice of samples
	//RMS is a running value
	for(int j = 0; j < samples.size(); j++){
		std::vector<short> slice;
	
		int low_bounds = std::max(j-samples_per_slice/2, 0);
		int high_bounds = std::min((int)(j+samples_per_slice/2), (int)samples.size());
	
		for(int i = low_bounds; i < high_bounds; i++){
			
			slice.push_back(samples[i]);
		}
		
		//Perform the volume correction on this single sample
		float rms = root_mean_square(slice);
		float constant = volume / rms;
		
		const short high = 0x7FFF; //highest value a sample can have
		
		float sf = (float)samples[j] * constant;
		short s = sf;
		if(sf > (float)high){
			s = high;
		}else if(sf < (float) -high){
			s = -high;
		}
		samples[j] = s;
		
		std::cout << "Sample " << j << " / " << samples.size() << std::endl;
	}
}
*/

void adjust_volume(float volume, std::vector<short>& samples){
	const int samples_per_slice = 1000;
	
	for(int j = 0; j < samples.size(); j += samples_per_slice){
		std::vector<short> slice;
		for(int i = 0; i < samples_per_slice && j+i < samples.size(); i++){
			slice.push_back(samples[j+i]);
		}
		float rms = root_mean_square(slice);
		//float rms_db = 20 * std::log10(rms);
		//float constant = std::pow((rms_db - volume)/20, 10);
		
		float constant = volume / rms;
		
		std::cout << "Constant: " << constant << std::endl;
		
		const short high = 0x7FFF; //highest value a sample can have
		
		for(int i = 0; i < slice.size(); i++){
			float sf = (float)slice[i] * constant;
			short s = sf;
			if(sf > (float)high){
				s = high;
			}else if(sf < (float) -high){
				s = -high;
			}
			slice[i] = s;
		}
		
		//replace the slice in samples
		for(int i = 0; i < samples_per_slice && j+i < samples.size(); i++){
			samples[j+i] = slice[i];
		}
	}
}

int main(int argc, char** argv){
  	if(argc != 3){
    	std::cout << "Usage: wavedit <filepath> <volume>\n";
    	return -1;
  	}

  	std::string filepath(argv[1]);
  	float volume;
  	try{
    	volume = std::stof(argv[2]);
  	}catch(std::exception& e){
    	std::cout << "Error: Could not parse volume as a number\n";
    	return -2;
  	}

  	std::vector<short> samples = getSamples(filepath);
	
	float rms = 20 * std::log10(root_mean_square(samples));
	std::cout << "RMS Volume: " << rms << std::endl;

	adjust_volume(volume, samples);
	writeSamples(getHeader(filepath), samples, filepath.substr(0, filepath.size()-4) + "-vol-adjusted.wav");

  	return 0;
}
