// Creator: @LEKPCSTEAM :https://github.com/LEKPCSTEAM

#include <Arduino.h>
#include <Wire.h>
#include <dw_font.h> // dw_utf8_gfont_library for UTF-8 font rendering
#include <SSD1306.h> // esp8266-oled-ssd1306 library work on ESP8266 and ESP32

#include "fonts/fonts.h"

SSD1306 display(0x3c, OLED_SDA, OLED_SCL); // Config in file platformio.ini
dw_font_t myfont;
void draw_pixel(int16_t x, int16_t y)
{
  display.setColor(WHITE);
  display.setPixel(x, y);
}
void clear_pixel(int16_t x, int16_t y)
{
  display.setColor(BLACK);
  display.setPixel(x, y);
}
void setup()
{
  uint16_t width = 0;
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  dw_font_init(&myfont,
               128,
               64,
               draw_pixel,
               clear_pixel);
  dw_font_setfont(&myfont, &font_th_sarabun_new_regular18);
  dw_font_goto(&myfont, 5, 28);
  dw_font_print(&myfont, "ภาษาไทย ^_^");
  display.display();

  delay(3000); // Wait for display to initialize
}
void loop()
{
  for (int i = 0; i < 128; i++)
  {
    display.clear();
    String msg = "นับ: " + String(i);
    dw_font_goto(&myfont, 10, 28);
    dw_font_print(&myfont, msg.c_str()); // Print the message
    Serial.println(msg);
    display.display();
    delay(500);
  }
}
