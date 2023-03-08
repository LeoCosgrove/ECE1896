#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputUSB            usb1;           //xy=381,412
AudioOutputI2S           i2s1;           //xy=667,406
AudioConnection          patchCord1(usb1, 0, i2s1, 0);
AudioConnection          patchCord2(usb1, 1, i2s1, 1);
// GUItool: end automatically generated code

void setup() {
  // put your setup code here, to run once:
  AudioMemory(10);

}

void loop() {
  // put your main code here, to run repeatedly:

}
