
int volumePin = 14;
float vin = 3.3;
int maxBitN = 1023;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println(calculateDB(volumePin));
  delay(1000);
}

float calculateDB(int pin) {
  float vout = analogRead(pin) * (vin/maxBitN);
  float dB = 20*log10(vin/vout);
  if(dB == INFINITY) {
    return 60;
  }
  return dB;
}
