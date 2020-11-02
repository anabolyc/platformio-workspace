#include <Arduino.h>
#include "main.h"

void setup() {
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(9600);
  Serial.println("Hello, world!");
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  Serial.println(millis());
  delay(10);
  digitalWrite(PIN_LED, LOW);

  delay(250);
}