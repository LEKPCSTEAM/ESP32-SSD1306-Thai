// Creator: @LEKPCSTEAM :https://github.com/LEKPCSTEAM

#include <Arduino.h>
#include <Wire.h>
#include <dw_font.h> // dw_utf8_gfont_library for UTF-8 font rendering
#include <SSD1306.h> // esp8266-oled-ssd1306 library

#include <ArduinoJson.h> 

#include "fonts/fonts.h"
#include "images.h"
extern const char WiFi_Logo_bits[] PROGMEM;
extern const char epd_bitmap_ROBO_Q_LOGO_26824_01[] PROGMEM;

#include <DHT.h> // DHT sensor library

// --- DHT Configuration ---
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --- OLED Configuration ---
SSD1306 display(0x3c, OLED_SDA, OLED_SCL); // กำหนด I2C OLED (กำหนดใน platformio.ini)
dw_font_t myfont;

// --- Draw Pixel Callback for dw_font ---
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
  Serial.begin(115200);

  display.init();
  display.flipScreenVertically();

  dw_font_init(&myfont, 128, 64, draw_pixel, clear_pixel);
  dw_font_setfont(&myfont, &font_th_sarabun_new_regular24);

  // Start I2C OLED
  dw_font_goto(&myfont, 5, 28);
  delay(1000);
  display.drawXbm(34, 20, rbq_imageWidth, rbq_imageHeight, epd_bitmap_ROBO_Q_LOGO_26824_01);
  display.display();
  delay(3000);
  dht.begin();
}

void loop()
{
  display.clear();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum))
  {
    dw_font_goto(&myfont, 0, 50);
    dw_font_print(&myfont, "อ่านค่า DHT ไม่ได้");
  }
  else
  {
    char line1[32], line2[32];
    snprintf(line1, sizeof(line1), "อุณหภูมิ: %.1f C", temp);
    snprintf(line2, sizeof(line2), "ความชื้น: %.1f %%", hum);

    // print json
    String jsonString;
    JsonDocument doc;
    doc["temperature"] = temp;
    doc["humidity"] = hum;
    serializeJson(doc, jsonString);
    Serial.println(jsonString);

    dw_font_goto(&myfont, 0, 20);
    dw_font_print(&myfont, line1);

    dw_font_goto(&myfont, 0, 50);
    dw_font_print(&myfont, line2);
  }

  display.display();
  delay(1000);
}
