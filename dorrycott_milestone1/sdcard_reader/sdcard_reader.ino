#include <SD.h>

int fileSelect = 0;
String file_name = "none";
int btn = 23;
File file;
bool is_pressed = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(23, INPUT_PULLDOWN);
  SD.begin(BUILTIN_SDCARD);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!is_pressed) {
    if(SD.exists(file_name.c_str())) {
      Serial.print(file.read());
    }
    if(digitalRead(btn) == HIGH) {
      if(SD.exists(file_name.c_str())) {
        file.close();
      }
      is_pressed = true;
    }
  }
  
  if(is_pressed) {
    fileSelect++;
    
    if(fileSelect >= 3) {
      fileSelect = 0;
    }
    
    switch(fileSelect) {
      case 0:
        file_name = "none";
        break;
      case 1:
        file_name = "moonbeach.wav";
        break;
      case 2:
        file_name = "rain.wav";
        break;
    }
    
    if(fileSelect > 0) {  //Reading a file
      if(SD.exists(file_name.c_str())) {  //Found file
        Serial.println("\nReading: " + file_name);
        file = SD.open(file_name.c_str());
      }
      else {  //Could not find file
        Serial.println("\nCould not find file");
      }
    }
    else {  //No noise selected
      Serial.println("\nNo file selected");
    }
    is_pressed = false;
  }
  delay(400);
}
