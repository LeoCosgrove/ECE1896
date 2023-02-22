#include <iostream>
#include <random>
using namespace std;

const int N = 500;
class Generator {
	default_random_engine generator;
	normal_distribution<double> distribution;
	double min, max;
public:
    Generator(double mean, double stddev, double min, double max):
        distribution(mean, stddev), min(min), max(max)
    {}

    int begin() {
        while (true) {
            double number = this->distribution(generator);
            if (number >= this->min && number <= this->max) {
                return number;
			}
        }
    }
};

int main() {
    Generator g(512, 150, 0, 1023);
    for (int i = 0; i < N; i++)
        cout << g.begin() << " "<< endl;
}
//https://www.socscistatistics.com/descriptive/histograms/ to test
