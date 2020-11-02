#include <avr/io.h>

int main () {
  DDRB = 1;                    // PB0 as an output
  TCCR0A = 1<<COM0A0;          // Toggle OC0A
  TCCR0B = 1<<WGM02 | 3<<CS00; // CTC mode and set prescaler to 64
  OCR0A = 3905;                // Frequency 2Hz
  while (1);
}