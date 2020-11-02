#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SD.h>
          
#include <AudioOutputI2SLJ.h>
#include <AudioFileSourceSPIFFS.h>
#include <AudioGeneratorWAV.h>

// TODO:
// I2SLJ : subclass from I2S
// AudioSource - Silence
// AudioSource - SIN generator
// AudioSource - SawTooth, SquareWave     

AudioOutputI2SLJ *out;
AudioFileSourceSPIFFS *file;
AudioGeneratorWAV *wav;

const uint8_t audio_files_length = 4;
const char **audio_files = (const char **) malloc(audio_files_length * sizeof(char *));

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#define LED_RED LED_BUILTIN

enum State
{
  STOP,
  WAIT,
  PLAY,
  ERR,
  END
};

void setup()
{
  WiFi.mode(WIFI_OFF);

  Serial.begin(115200);                                       
  Serial.println("Starting up...\n");
  out = new AudioOutputI2SLJ();
  wav = new AudioGeneratorWAV();

  
  audio_files[0] = "/1000Hz_-3dBFS_2s.wav";
  audio_files[1] = "/2000Hz_-3dBFS_2s.wav";
  audio_files[2] = "/10000Hz_-3dBFS_2s.wav";
  audio_files[3] = "/20000Hz_-3dBFS_2s.wav";
}

State state = STOP;
int seq = 0;

void loop()
{

  switch (state)
  {
  case WAIT:
    delay(250);
    Serial.println(" <");
    state = STOP;
    break;

  case STOP:
    Serial.print("> ");
    if (file)
      free(file);

    seq++;
    Serial.print(audio_files[seq % audio_files_length]);
    file = new AudioFileSourceSPIFFS(audio_files[seq % audio_files_length]);

    if (wav->begin(file, out))
    {
      state = PLAY;
    }
    else
    {
      state = ERR;
    }
    break;

  case PLAY:
    if (wav->isRunning())
    {
      if (!wav->loop())
      {
        wav->stop();
        state = WAIT;
      }
    }
    break;

  case ERR:
    Serial.println("error!");
    state = END;
    break;

  case END:
    break;
  }
}