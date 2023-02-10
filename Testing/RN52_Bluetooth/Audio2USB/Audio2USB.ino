#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AsyncAudioInputSPDIF3    spdif_async1;   //xy=206,409
AudioInputI2S            i2s1;           //xy=236,540
AudioAmplifier           amp1;           //xy=503,416
AudioOutputUSB           usb1;           //xy=742,422
AudioConnection          patchCord1(spdif_async1, 0, amp1, 0);
AudioConnection          patchCord2(amp1, 0, usb1, 0);
AudioConnection          patchCord3(amp1, 0, usb1, 1);
// GUItool: end automatically generated code

void setup() {
  AudioMemory(12);
  amp1.gain(1);
}

void loop() {

}