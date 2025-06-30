#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

// Piny
#define TFT_CS     10
#define TFT_DC     9
#define TFT_RST    8
#define TOUCH_CS   4
#define TOUCH_IRQ  2
#define SD_CS 5

#define TS_MINX 200
#define TS_MAXX 3900
#define TS_MINY 200
#define TS_MAXY 3900

#define BRUSH_RADIUS 4
#define BRUSH_COLOR ILI9341_WHITE
#define BTN_X 190
#define BTN_Y 10
#define BTN_W 40
#define BTN_H 30


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);


void setup() {
  tft.begin();
  touch.begin();
  touch.setRotation(1);
  tft.setRotation(1);
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(10, 10);
  tft.println("Paint");
  
  drawClearButton();
}

void loop() {
  if (touch.touched()) {
    TS_Point p = touch.getPoint();

    int x = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());

    if (x > BTN_X && x < BTN_X + BTN_W && y > BTN_Y && y < BTN_Y + BTN_H) {
      tft.fillScreen(ILI9341_BLACK);
      drawClearButton();
      return;
    }
  tft.fillCircle(x, y, BRUSH_RADIUS, BRUSH_COLOR);
  }

  
}

void drawClearButton() {
  tft.fillRect(BTN_X, BTN_Y, BTN_W, BTN_H, ILI9341_RED);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(BTN_X + 5, BTN_Y + 8);
  tft.print("clear");
}