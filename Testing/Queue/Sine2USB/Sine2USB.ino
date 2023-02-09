/*
 * A simple queue test which generates a sine wave in the 
 * application and sends it to headphone jack. The results
 * should always be a glitch-free wave, but various options
 * can be changed to modify the usage of audio blocks, and an
 * ability to execute the loop() function more slowly, with
 * simple waveform generation, or more efficiently / faster,
 * but requring some programmer effort to re-try if sending
 * waveform data fails due to a lack of buffer or queue space.
 *
 * This example code is in the public domain.
 * 
 * Jonathan Oakley, November 2021
 */
 
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayQueue           queue1;         //xy=212,248
AudioInputI2S            i2s1;           //xy=277,351
AudioOutputI2S           i2s2;           //xy=277,351
AudioOutputUSB           usb1;           //xy=637.8888549804688,243.88888549804688
AudioConnection          patchCord2(queue1, 0, usb1, 0);
AudioConnection          patchCord3(queue1, 0, usb1, 1);
// GUItool: end automatically generated code

uint32_t next;
void setup() {
  AudioMemory(10);
  next = millis();
  queue1.setMaxBuffers(4);
}


/*
 * Generate one sample of a waveWform.
 * Currently 220Hz sine wave, but could make it more complex.
 */
int16_t nextSample()
{
  static float phas = 0.f;
  int16_t result = (int16_t) (sin(phas)*8000.);
  
  phas += 220./AUDIO_SAMPLE_RATE_EXACT*TWO_PI;
  if (phas > TWO_PI)
    phas -= TWO_PI;  
  return result;
}


int loops;
int nulls;

void loop() {
  int16_t* buf = queue1.getBuffer();
  if (NULL == buf)
    nulls++;
  else
  {
    for (int i=0;i<AUDIO_BLOCK_SAMPLES;i++)
      buf[i] = nextSample();
    queue1.playBuffer();
  }
  loops++;
  if (millis() > next)
  {
    next += 100; // aim to output every 100ms
  }
}
