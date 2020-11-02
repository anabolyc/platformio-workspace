#include <Arduino.h>
#include "main.h"

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_OUT, OUTPUT);
  pinMode(PIN_IN, INPUT);

  Serial.begin(9600);
  Serial.println("Hello, world!");
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_OUT, HIGH);
  delay(1);

  uint16_t inv = analogRead(PIN_IN);
  Serial.println(inv);

  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_OUT, LOW);

  delay(100);
}