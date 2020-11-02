#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "main.h"

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(DISPLAY_PIN_DC, DISPLAY_PIN_CE, DISPLAY_PIN_RST);

#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;

void setup()
{
  Serial.begin(SERIAL_SPEED);
  while (!Serial)
    _delay_ms(1);

  display.begin();
  display.setContrast(DISPLAY_CONTRAST);
  display.setTextSize(0);
  display.setTextColor(BLACK);

  if (!ina219.begin())
  {
    Serial.println("Failed to find INA219 chip");
    while (1)
      _delay_ms(10);
  }
  ina219.setCalibration_16V_400mA();
}

uint32_t last_measurement = 0;

void loop()
{
  uint32_t started = millis();
  update_power_display();
  Serial.println();
  // _delay_ms(100);
}

float total_mA_ms  = 0.0;

void update_power_display() {
  // Read voltage and current from INA219.
  float shuntvoltage = ina219.getShuntVoltage_mV();
  float busvoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA() / 10.;
  if (current_mA < 0)
    current_mA = 0;

  // Compute load voltage, power, and milliamp-hours.
  float loadvoltage = busvoltage + (shuntvoltage / 1000);
  float power_mW = loadvoltage * current_mA;

  display.clearDisplay();

  display.setCursor(0, 0);
  display.setTextColor(BLACK);
  display.print(F("VCC, V= ")); 
  display.setTextColor(WHITE, BLACK);
  display.println(loadvoltage); 
  Serial.print(loadvoltage);
  Serial.print('\t');

  display.setTextColor(BLACK);
  display.print(F("CUR,mA= ")); 
  display.setTextColor(WHITE, BLACK);
  display.println(current_mA); 
  Serial.print(current_mA);
  Serial.print('\t');

  display.setTextColor(BLACK);
  display.print(F("PWR,mW= ")); 
  display.setTextColor(WHITE, BLACK);
  display.println(power_mW); 
  Serial.print(power_mW);
  Serial.print('\t');

  uint32_t passed_ms = millis() - last_measurement;
  Serial.print(F("+"));
  Serial.print(passed_ms);
  Serial.print('\t');
  last_measurement = millis();

  uint32_t total_sec = last_measurement / 1000.0;
  uint32_t sec = total_sec % 60;
  uint32_t min = (total_sec - sec) / 60;
  display.setTextColor(BLACK);
  display.print(F("TIME  = ")); 
  display.setTextColor(WHITE, BLACK);
  display.print(min); 
  display.setTextColor(BLACK);
  display.print(F(":")); 
  display.setTextColor(WHITE, BLACK);
  if (sec < 10) display.print(F("0")); 
  display.println(sec); 
  Serial.print(total_sec);
  Serial.print('\t');

  total_mA_ms += current_mA * passed_ms;
  float total_mAs = total_mA_ms / 1000.; // 3600.0;

  display.setTextColor(BLACK);
  display.print(F("CP,mAs= ")); 
  display.setTextColor(WHITE, BLACK);
  display.println(total_mAs); 
  Serial.print(total_mAs);
  Serial.print('\t');

  // Serial.println();
  display.display();
  
}