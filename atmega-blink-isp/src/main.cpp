#include <Arduino.h>
#define PIN_LED LED_BUILTIN

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

uint8_t state = 0;

void loop() {
  digitalWrite(PIN_LED, state++ % 2 == 0 ? HIGH : LOW);
  delay(100);
}