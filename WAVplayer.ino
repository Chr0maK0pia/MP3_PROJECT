#include "AudioTools.h"
#include "AudioTools/AudioCodecs/CodecWAV.h"
#include "AudioTools/Disk/AudioSourceSD.h"

const char *startFilePath = "/";
const char* ext = "wav";

AudioSourceSD source(startFilePath, ext, 10);
AnalogAudioStream out;
WAVDecoder wav;
AudioPlayer player(source, out, wav);
//fuck this
void setup() {
  Serial.begin(115200);
  while (!Serial);

  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  if (!source.begin()) {
    Serial.println("SD failed!");
    while (1);
  }

  Serial.println("SD OK");


  auto config = out.defaultConfig(audio_tools::TX_MODE);
  config.sample_rate = 11025;
  config.channels = 1;
  config.bits_per_sample = 16;

  out.begin(config);


  player.begin();
}

void loop() {
  player.copy();
}