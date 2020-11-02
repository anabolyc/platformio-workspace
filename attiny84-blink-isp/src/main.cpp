#include <Arduino.h>
#include <util/delay.h>

// #define PIN_LED_1 PA1 PB2
// #define PIN_LED_2 PA2
// #define PIN_LED_3 PA3

#define PIN_START  7
#define PINS_COUNT 3 

void setup() {
  // pinMode(PIN_LED_1, OUTPUT);
  // pinMode(PIN_LED_2, OUTPUT);
  // pinMode(PIN_LED_3, OUTPUT);
  for (uint8_t i = PIN_START; i < PINS_COUNT; i++)
    pinMode(i, OUTPUT);
}

uint8_t state = 0;

void loop() {
  // state++;
  // digitalWrite(PIN_LED_1, state % 0 == 0 ? HIGH : LOW);
  // digitalWrite(PIN_LED_2, state % 1 == 0 ? HIGH : LOW);
  // digitalWrite(PIN_LED_3, state % 2 == 0 ? HIGH : LOW);
  // delay(500);
  uint8_t pinNumber = PIN_START + (state++ % PINS_COUNT);
  digitalWrite(pinNumber, HIGH);
  if (pinNumber - PIN_START == 2)
    _delay_ms(2000);
  else 
    _delay_ms(2000);
  digitalWrite(pinNumber, LOW);
  _delay_ms(500);
}