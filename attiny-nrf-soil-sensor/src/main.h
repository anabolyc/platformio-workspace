#include <avr/io.h>

#define SLEEP_16ms 0
#define SLEEP_32ms 1
#define SLEEP_64ms 2
#define SLEEP_128ms 3
#define SLEEP_256ms 4
#define SLEEP_512ms 5
#define SLEEP_1024ms 6
#define SLEEP_2048ms 7
#define SLEEP_4096ms 8
#define SLEEP_8192ms 9

#define PIN_PWR_SW PINB3
#define PIN_PWR_SW_ _BV(PINB3)

// void setup();
// void loop();
void setup_watchdog(int mode);
void sleep(int mode);