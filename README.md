# ESP32-SSD1306-THAI

ใช้งานจอ OLED ขนาด 128x64 (SSD1306) ร่วมกับ ESP32/ESP8266 เพื่อแสดงข้อความภาษาไทยด้วยฟอนต์ Sarabun บน Arduino framework ผ่าน PlatformIO

## 🔧 ความสามารถ

- แสดงผลข้อความภาษาไทยแบบ UTF-8
- ใช้ไลบรารี `dw_utf8_gfont_library` สำหรับวาดฟอนต์
- ใช้ไลบรารี `esp8266-oled-ssd1306` สำหรับควบคุมหน้าจอ OLED
- แสดงผลข้อความแบบไดนามิกจากตัวแปร `String`

## ScreenShot

<p align="center">
  <img src="/docs/1.jpg" width="300" />
  <img src="/docs/2.jpg" width="300" />
  <img src="/docs/3.jpg" width="300" />
</p>



## 📁 โครงสร้างโปรเจกต์

```
lib/
├── dw_utf8_gfont_library/     ← ไลบรารีฟอนต์ UTF-8 (dw_font)
├── esp8266-oled-ssd1306/      ← ไลบรารีจอ OLED SSD1306
src/
├── fonts/                     ← ไฟล์ฟอนต์ภาษาไทย
│   ├── font_th_sarabun_new_regular18.c
│   └── ...
├── main.cpp                   ← ตัวอย่างโค้ดหลัก
```

## ⚙️ การติดตั้ง

1. ติดตั้ง [PlatformIO](https://platformio.org/)
2. เปิดโปรเจกต์นี้ใน VS Code
3. ต่อสายบอร์ด ESP32/ESP8266 เข้ากับคอมพิวเตอร์
4. กด `Upload` เพื่ออัปโหลด

## 📌 การตั้งค่า `platformio.ini`

```
[env]
platform = espressif32
framework = arduino
monitor_speed = 115200

[env:esp32dev]
board = esp32dev
build_flags =
    -D OLED_SDA=21
    -D OLED_SCL=22

[env:esp32-c3]
board = esp32-c3-devkitc-02
build_flags =
    -D ARDUINO_USB_CDC_ON_BOOT=1
    -D ARDUINO_USB_MODE=1
    -D OLED_SDA=8
    -D OLED_SCL=9
```

### ✅ วิธีใช้ dwFontExporter

1. **เปิดโปรแกรม**
    
    รัน `dwFontExporter.exe` บน Windows (ไม่ต้องติดตั้ง)
    
2. **เลือกฟอนต์**
    - กดปุ่ม `...` เพื่อเลือกไฟล์ฟอนต์ `.ttf` เช่น `THSarabunNew.ttf`
    - หรือเลือกฟอนต์จากรายชื่อที่ติดตั้งในระบบ
3. **ตั้งค่าฟอนต์**
    - กำหนดขนาดฟอนต์ (เช่น `18`)
    - เลือก **Charset** เป็น `UTF-8`
    - เลือก Unicode Range เช่น:
        - `U+0E00–U+0E7F` → สำหรับภาษาไทย
4. **ตั้งชื่อฟอนต์**
    - ใส่ชื่อที่ใช้ในโค้ด เช่น `font_th_sarabun_new_regular18`
5. **กดปุ่ม `Export`**
    - จะได้ไฟล์ `.c` และ `.h` ที่ใช้ในโปรเจกต์ Arduino/ESP32
6. **นำไฟล์ไปใช้**
    - วางไว้ในโฟลเดอร์โปรเจกต์ (`src/fonts`)
    - แก้ไข `fonts.h` ให้มี `extern const dw_font_info_t font_th_sarabun_new_regular18;`
    - ใช้ในโค้ดด้วย `dw_font_setfont(...)`
    

## 🙏 เครดิต

- ฟอนต์ภาษาไทยและไลบรารี `dw_utf8_gfont_library` โดยคุณ Praphas —
    
    🔗 https://www.praphas.com/forum/index.php?topic=314.0
    
    🔗 https://github.com/deaware/dw_utf8_gfont_library
    
- ไลบรารี SSD1306 จาก
    
    🔗 https://github.com/ThingPulse/esp8266-oled-ssd1306