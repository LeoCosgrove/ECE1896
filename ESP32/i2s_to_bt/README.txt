This takes whatever i2s input the ESP32 recieves and outputs it to a bluetooth device "WorkTunes". Assumes i2s1 pin output from teensy (not i2s2).

Pins:
Connect grounds and power of teensy and esp together

Pin:	Teensy	-	ESP
SD	7		GPIO32
WS	20		GPIO15
SCK	21		GPIO14
