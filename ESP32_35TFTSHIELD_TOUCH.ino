
/*
 * 3.5" TFT LCD Shield
 * 
 * LCD Pins for ESP32
 * RD=2, WR=4, RS=15, CS=33, RST=32
 * D0=12, D1=13, D2=26, D3=25, D4=17, D5=16, D6=27, D7=14
 * 
 * TOUCH Pins for ESP32
 * YP=33, XM=15, YM=13, XP=12
 */

#include <SPI.h>
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include "TouchScreen_kbv.h"

#define LCD_RD  2
#define LCD_WR  4
#define LCD_RS 15
#define LCD_CS 33
#define LCD_RST 32

#define LCD_D0 12
#define LCD_D1 13
#define LCD_D2 26
#define LCD_D3 25
#define LCD_D4 17
#define LCD_D5 16
#define LCD_D6 27
#define LCD_D7 14

#define TOUCH_YP 33
#define TOUCH_XM 15
#define TOUCH_YM 13
#define TOUCH_XP 12

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

MCUFRIEND_kbv tft;
TouchScreen_kbv ts(TOUCH_XP, TOUCH_YP, TOUCH_XM, TOUCH_YM, 300);
TSPoint_kbv tp;

void setup(void) {
    Serial.begin(115200);
    if (!Serial) delay(5000); 

    uint16_t ID = tft.readID();
    Serial.print("ID = 0x");
    Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; 
    tft.begin(ID);

    tft.println("Init Done !");
}

/*
 * Touch horizontal verkehrt
 * LO X-100 Y-100
 * LU X-900 Y-100
 * RO X-100 Y-900
 * RU X-900 Y-900
 */

#define touchX_left_top 100
#define touchY_left_top 100

#define touchX_right_down 900
#define touchY_right_down 900

void loop(void) {
  readTouch();
  if(tp.z > 200) {
    Serial.print("X: ");
    Serial.println(tp.x);
    Serial.print("y: ");
    Serial.println(tp.y);
    Serial.print("z: ");
    Serial.println(tp.z);
    Serial.println();
  }
}

void readTouch(void) {
  tp = ts.getPoint();
  pinMode(TOUCH_YP, OUTPUT);
  pinMode(TOUCH_XM, OUTPUT);
}
