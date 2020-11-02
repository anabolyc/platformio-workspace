#ifndef __MAIN_H__
#define __MAIN_H__

#include <Wire.h>
#include <ESP8266WiFi.h>16 // D0

// 5-pin config
#define NRF_CE    4
#define NRF_CSN   15

#define SHIFT_DATA 2 // D4 //16 // D0
#define SHIFT_EN   0 // D3 //2 // D4 
#define SHIFT_CLOCK 5 // D1 //5 // D1
#define SHIFT_LATCH 16 // D0 //0 // D3

#define SERIAL_SPEED 115200

void registerWrite(byte data);

#endif
