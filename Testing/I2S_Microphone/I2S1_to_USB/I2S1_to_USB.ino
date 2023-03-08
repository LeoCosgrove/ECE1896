#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=121,240
AudioFilterBiquad        biquad1;        //xy=297,241
AudioAmplifier           amp1;           //xy=450,242
AudioOutputUSB           usb1;           //xy=636.8888549804688,241.88888549804688
AudioConnection          patchCord1(i2s1, 0, biquad1, 0);
AudioConnection          patchCord2(biquad1, amp1);
AudioConnection          patchCord3(amp1, 0, usb1, 1);
AudioConnection          patchCord4(amp1, 0, usb1, 0);
// GUItool: end automatically generated code



void setup() {
  // put your setup code here, to run once:
  AudioMemory(10);
  biquad1.setHighpass(0,80);
  amp1.gain(1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
