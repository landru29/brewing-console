#include "keyboard.h"
#include <string.h>

/*byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};*/


Keyboard::Keyboard() {
  byte rowPins_[ROWS] = {9, 8, 7, 6};
  byte colPins_[COLS] = {5, 4, 3, 2};
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
