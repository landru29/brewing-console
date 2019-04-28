#include "screen.h"
#include "splash.h"

#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)


#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


Screen::Screen() {
  Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  
}

void Screen::init() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  clearDisplay();
  drawBitmap((WIDTH - landruSplash_width) / 2, (HEIGHT - landruSplash_height) / 2,
      landruSplash_data, landruSplash_width, landruSplash_height, 1);
}

void Screen::clearLine(uint8_t line) {
  setCursor(0, line);
  println("                      ");
}
