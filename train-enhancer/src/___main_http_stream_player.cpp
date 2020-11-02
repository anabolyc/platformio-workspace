// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <SD.h>

// #include "AudioFileSourceHTTPStream.h"
// #include "AudioFileSourceBuffer.h"
// #include "AudioGeneratorMP3.h"
// #include "AudioOutputI2S.h"

// const char *SSID = "wifi-12-private";
// const char *PASSWORD = "9263777101";

// // Randomly picked URL
// const char *URL="http://192.168.1.110:8000/ices";

// AudioGeneratorMP3 *mp3;
// AudioFileSourceHTTPStream *file;
// AudioFileSourceBuffer *buff;
// AudioOutputI2S *out;

// // Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
// void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
// {
//   const char *ptr = reinterpret_cast<const char *>(cbData);
//   (void) isUnicode; // Punt this ball for now
//   // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
//   char s1[32], s2[64];
//   strncpy_P(s1, type, sizeof(s1));
//   s1[sizeof(s1)-1]=0;
//   strncpy_P(s2, string, sizeof(s2));
//   s2[sizeof(s2)-1]=0;
//   Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, s1, s2);
//   Serial.flush();
// }

// // Called when there's a warning or error (like a buffer underflow or decode hiccup)
// void StatusCallback(void *cbData, int code, const char *string)
// {
//   const char *ptr = reinterpret_cast<const char *>(cbData);
//   // Note that the string may be in PROGMEM, so copy it to RAM for printf
//   char s1[64];
//   strncpy_P(s1, string, sizeof(s1));
//   s1[sizeof(s1)-1]=0;
//   Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
//   Serial.flush();
// }

// void setup()
// {
//   Serial.begin(115200);
//   delay(1000);
//   Serial.println("Connecting to WiFi");

//   WiFi.disconnect();
//   WiFi.softAPdisconnect(true);
//   WiFi.mode(WIFI_STA);
  
//   WiFi.begin(SSID, PASSWORD);

//   // Try forever
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.println("...Connecting to WiFi");
//     delay(1000);
//   }
//   Serial.println("Connected");

//   file = new AudioFileSourceHTTPStream(URL);
//   file->RegisterMetadataCB(MDCallback, (void*)"ICY");
//   buff = new AudioFileSourceBuffer(file, 2048);
//   buff->RegisterStatusCB(StatusCallback, (void*)"buffer");
//   out = new AudioOutputI2S();
//   mp3 = new AudioGeneratorMP3();
//   mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");

//   Serial.println("Starting player:");  
//   Serial.println(URL);
//   mp3->begin(buff, out);
// }

// void loop()
// {
//   static int lastms = 0;

//   if (mp3->isRunning()) {
//     if (millis()-lastms > 1000) {
//       lastms = millis();
//       Serial.printf("Running for %d ms...\n", lastms);
//       Serial.flush();
//      }
//     if (!mp3->loop()) mp3->stop();
//   } else {
//     Serial.printf("MP3 done\n");
//     delay(1000);
//   }
// }

