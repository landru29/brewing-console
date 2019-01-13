#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Keypad.h>


#define ROWS  4
#define COLS  4



class Keyboard {

  public:
    Keyboard();
    char getKey();

  private:
    Keypad* pad;
    byte rowPins[ROWS];
    byte colPins[COLS];
    char hexaKeys[ROWS][COLS];
  
};



#endif
