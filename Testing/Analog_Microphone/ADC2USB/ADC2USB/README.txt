This program takes the microphone input on the specified analog input pin and passes it through as a USB recording device. Some light filtering is done to the signal.

Note: input from ADC can have a lot of noies from within the chip itself, oversampling using the AnalogRead() function may be a better alternative.