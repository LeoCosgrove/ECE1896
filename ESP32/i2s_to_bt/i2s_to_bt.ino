#include "AudioTools.h"
#include "AudioLibs/AudioA2DP.h"
#include "AudioTools/AudioStreamsConverter.h"

int channels = 2;
I2SStream i2sStream; // Access I2S as stream
A2DPStream a2dpStream;                          // access A2DP as stream
NumberFormatConverterStream sound16(i2sStream);
StreamCopy copier(a2dpStream, sound16); // copy i2sStream to csvStream

// Arduino Setup
void setup(void) {
    //Serial.begin(115200);
    //AudioLogger::instance().begin(Serial, AudioLogger::Info);

      // start bluetooth
    auto cfgA2DP = a2dpStream.defaultConfig(TX_MODE);
    cfgA2DP.name = "WorkTunes";
    a2dpStream.begin(cfgA2DP);
    
    auto cfg = i2sStream.defaultConfig(RX_MODE);
    cfg.i2s_format = I2S_STD_FORMAT; // or try with I2S_LSB_FORMAT
    cfg.bits_per_sample = 32;
    cfg.channels = channels;
    cfg.sample_rate = 44100;
    cfg.is_master = false;
     // this module nees a master clock if the ESP32 is master
    cfg.use_apll = false;  // try with yes
    cfg.buffer_size = 128;
    i2sStream.begin(cfg);
    sound16.begin(32,16);
}

// Arduino loop - copy data
void loop() {
    copier.copy();
}

