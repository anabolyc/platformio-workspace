#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_MAX_ROWS 8
#define SCREEN_ROW_HEIGHT 8

#ifdef HW_SPI
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
#else
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
#endif

#define SW_SERIAL_RX 8
#define SW_SERIAL_TX 7