#include <ESP8266WiFi.h>
#include <Arduino.h>

#define LED_PIN LED_BUILTIN
#define SERIAL_SPEED 9600

void setup() {
  WiFi.mode(WIFI_OFF);
  Serial.begin(SERIAL_SPEED);
  pinMode(LED_PIN, OUTPUT);
  Serial.println(F("Hello, World!"));
}

uint8_t state = 0;

void loop() {
  digitalWrite(LED_PIN, state++ % 2 ==0 ? HIGH : LOW);
  Serial.print('.');
  delay(500);
}