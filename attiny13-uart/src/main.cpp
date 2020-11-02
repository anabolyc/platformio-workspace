#include <Arduino.h>
#include <util/delay.h>
 
#define SERIAL_BAUD 19200

//SoftwareSerial mySerial(PIN_RX, PIN_TX);

#define PINS_COUNT 4

void setup() {
  for (uint8_t i = 0; i < PINS_COUNT; i++)
    pinMode(i, OUTPUT);
  _delay_ms(100);
  
  Serial.begin(SERIAL_BAUD);
  Serial.println(F("Hello,")); 
  Serial.println(F("I'm")); 
  Serial.println(F("ATTINY13!"));
}

uint8_t state = 0;

void loop() {
  uint8_t pinNumber = state++ % PINS_COUNT;
  digitalWrite(pinNumber, HIGH);
  _delay_ms(250);
  digitalWrite(pinNumber, LOW);
  //Serial.println(millis());
  _delay_ms(250);
}

