#include "keyboard.h"
#include <string.h>


Keyboard::Keyboard() {
  byte rowPins_[ROWS] = {5, 6, 7, 8};
  byte colPins_[COLS] = {9, 10, 11, 12};
  char hexaKeys_[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };
  memcpy(rowPins, rowPins_, ROWS);
  memcpy(colPins, colPins_, COLS);
  memcpy(hexaKeys, hexaKeys_, ROWS*COLS);
  
  pad = new Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
}

char Keyboard::getKey() {
  return pad->getKey();
}
