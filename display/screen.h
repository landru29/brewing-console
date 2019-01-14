#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_SSD1306.h>

class Screen: public Adafruit_SSD1306 {
  public:
    Screen();
    void init();
    void clearLine(uint8_t line);
};

#endif
