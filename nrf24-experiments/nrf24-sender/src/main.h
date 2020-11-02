#ifndef __MAIN_H__
#define __MAIN_H__

//  SERIAL TX ON PIN 3
#include "SoftwareSerial.h"
#define SERIAL_RX 7
#define SERIAL_TX 3

//  RADIO on SPI pins
// 3-pin config
// #define NRF_CE    3
// #define NRF_CSN   3
// 4-pin config
//#define NRF_CE    6
//#define NRF_CSN   4
// 5-pin config
#define NRF_CE    3
#define NRF_CSN   4

//  SENSOR on A2 = pin #4
//#define SENS_PIN A2

#define SERIAL_SPEED 115200

#endif
