#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//TODO: try differential reading

// GUItool: begin automatically generated code
AudioInputI2S i2s1;     //xy=228,331
AudioPlayQueue queue1;  //xy=236,256
AudioAmplifier amp1;    //xy=450,273
AudioOutputUSB usb1;    //xy=924,316
AudioFilterBiquad        biquad1;        //xy=446,296
AudioConnection patchCord1(queue1, biquad1);
AudioConnection patchCord3(biquad1, 0, usb1, 0);
AudioConnection patchCord4(biquad1, 0, usb1, 1);
// GUItool: end automatically generated code

#define INPUT_PIN A2
#define NUM_SAMPLES 1
#define READ_RES 10
uint32_t next;

void setup() {
  AudioMemory(10);
  pinMode(INPUT_PIN, INPUT);
  queue1.setMaxBuffers(4);
  biquad1.setLowpass(0,20000);
  biquad1.setHighpass(1,20);
  analogReadAveraging(NUM_SAMPLES); 
  analogReadRes(READ_RES);
}

void loop() {
  int16_t* buf = queue1.getBuffer();
  if (!(NULL == buf)) {
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
      buf[i] = 10*analogRead(INPUT_PIN);
    }
    queue1.playBuffer();
  }
}