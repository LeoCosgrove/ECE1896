This program outputs a sine wave over the external DAC by using the built in sine generation.

PINS FOR CS4344 DAC, USING I2S1:

DAC - Teensy
SDIN (1) - 7
DEM/SCLK (2) - 21
LRCK (3) - 20
MCLK (4) - 23
VQ (5) - tie to ground with two caps in parallel (0.1uf and 10uf)
FILT+ (6) - tie to ground with 10uf cap
AOUTL (7) left output
GND (8) - GND
VA (9) - 3.3V
AOUTR (10) - right output