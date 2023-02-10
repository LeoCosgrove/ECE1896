#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define HWSERIAL Serial1

void setup() {
  Serial.begin(115200);
  HWSERIAL.begin(115200);
}

void loop() {
  if (Serial.available()) {      // If anything comes in Serial (USB),
    HWSERIAL.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
  }

  if (HWSERIAL.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(HWSERIAL.read());   // read it and send it out Serial (USB)
  }
}