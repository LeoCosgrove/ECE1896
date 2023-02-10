#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1(A2);           //xy=215,298
AudioFilterBiquad        biquad1;        //xy=446,296
AudioAmplifier           amp1;           //xy=671,305
AudioOutputUSB           usb1;           //xy=924,316
AudioInputI2S            i2s1;
AudioConnection          patchCord1(adc1, biquad1);
AudioConnection          patchCord2(biquad1, amp1);
AudioConnection          patchCord3(amp1, 0, usb1, 0);
AudioConnection          patchCord4(amp1, 0, usb1, 1);
// GUItool: end automatically generated code


void setup() {
  AudioMemory(10);
  biquad1.setLowpass(0,20000);
  biquad1.setHighpass(1,20);
  amp1.gain(20);
}

void loop() {
  // put your main code here, to run repeatedly:

}
