#include <Arduino.h>
#define HW_SPI

#include "main.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <SoftwareSerial.h>
SoftwareSerial SSerial(SW_SERIAL_RX, SW_SERIAL_TX);

#ifdef HW_SPI
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#else
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         &SPI, OLED_DC, OLED_RESET, OLED_CS);
#endif

#define UART_BAUD 9600
#define packTimeout 5 // ms (if nothing more on UART, then send packet)
#define bufferSize 128

void testdrawchar(void)
{
  display.clearDisplay();

  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);             // Start at top-left corner
  display.cp437(true);                 // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for (int16_t i = 0; i < 256; i++)
  {
    if (i == '\n')
      display.write(' ');
    else
      display.write(i);
  }

  display.display();
  delay(2000);
}

void setup()
{
  Serial.begin(UART_BAUD);
  SSerial.begin(UART_BAUD);
  SSerial.listen();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);

  // test height
  // for (uint8_t i = 0; i < 128; i++)
  // {
  //   display.setCursor(i, i * 8);
  //   display.write(i + '0');
  //   display.write('\n');
  // }

  // // test width
  // for (uint8_t i = 0; i < 128; i++)
  // {
  //   display.setCursor(i * 6, 0);
  //   display.write((i % 10) + '0');
  //   display.write('\n');
  // }

  // display.display();
  Serial.write("Ready!\n");
}

uint8_t row_index = 0;

uint8_t buf[bufferSize];
uint8_t i = 0;

void loop()
{
  if (SSerial.available())
  {
    // uint8_t cursor_y = display.getCursorY() % SCREEN_HEIGHT;
    // uint8_t cursor_x = display.getCursorX();
    // //display.clearDisplay();
    // display.drawFastHLine(cursor_x, cursor_y, SCREEN_WIDTH, SSD1306_BLACK);
    // display.setCursor(cursor_x, cursor_y);

    Serial.write('\n');
    Serial.write('+');
    while (1)
    {
      if (SSerial.available())
      {
        buf[i] = (char)SSerial.read();
        if (i < bufferSize - 1)
          i++;
      }
      else
      {
        //delayMicroseconds(packTimeoutMicros);
        //delay(packTimeout);
        if (!SSerial.available())
        {
          Serial.print(i);
          Serial.write(' ');
          break;
        }
      }
    }

    // now send to WiFi:
    // display.write((char *)buf, i);
    // display.display();
    for (uint8_t j = 0; j < i; j++)
    {
      // Serial.print(buf[j]);
      // Serial.write('|');
      Serial.print((char)buf[j]);
      
      // if (buf[j] == 13)
      // {
      //   uint8_t cursor_y = display.getCursorY();
      //   for (uint8_t k = 0; k < SCREEN_ROW_HEIGHT; k++) 
      //     display.drawFastHLine(0, cursor_y + k, SCREEN_WIDTH, SSD1306_BLACK);
      // }

      display.print((char)buf[j]);
      
      // if (buf[j] == 13 && display.getCursorY() >= SCREEN_HEIGHT - SCREEN_ROW_HEIGHT)
      // {
      //   uint8_t cursor_y = 0; //display.getCursorY() % SCREEN_HEIGHT;
      //   uint8_t cursor_x = display.getCursorX();
      //   display.clearDisplay();
      //   display.setCursor(cursor_x, cursor_y);
      // }
    }

    // Serial.print('+');
    display.display();

    //display.setCursor((row_index++ * 8) % SCREEN_HEIGHT, 0);
    i = 0;
  }
}
