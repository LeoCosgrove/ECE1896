#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=182,370
AudioAmplifier           amp1;           //xy=442,360
AudioOutputI2S           i2s1;           //xy=704,359
AudioConnection          patchCord1(sine1, amp1);
AudioConnection          patchCord2(amp1, 0, i2s1, 0);
AudioConnection          patchCord3(amp1, 0, i2s1, 1);
// GUItool: end automatically generated code


void setup() {
  AudioMemory(10);
  sine1.amplitude(1);
  sine1.frequency(200);
  sine1.phase(0);
  amp1.gain(10);
}

void loop() {
  
}
