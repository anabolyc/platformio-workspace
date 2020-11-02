#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"
#include <Arduino.h>

void setup() {
  DDRB = DDRB | PIN_PWR_SW_;
  PORTB = 0x00;
}

void loop() {
  PORTB |= PIN_PWR_SW_;
  //sleep(SLEEP_1024ms);
  _delay_ms(1024);
  PORTB &= ~PIN_PWR_SW_;
  sleep(SLEEP_2048ms);
}

// =============== SLEEP MODE ===============

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void sleep(int mode) {
  setup_watchdog(mode);
  cbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter OFF
  DDRB = 0x00;                         // all pins are high impedance inputs
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();                        // System actually sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out
  DDRB = DDRB | PIN_PWR_SW_;           // Restore pin mode
  sbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter ON
}

void setup_watchdog(int ii) {
  uint8_t bb = ii & 7;
  if (ii > 7) 
    bb |= (1 << 5);
  bb |= (1 << WDCE);
  int ww = bb;

  MCUSR &= ~(1 << WDRF);
  // start timed sequence
  WDTCR |= (1 << WDCE) | (1 << WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}
