
#include "motor.h"
#include "keyboard.h"
#include "string.h"
#include <Wire.h>

#define BUFFER_SIZE 20

int maxFreq = 65000;

Keyboard customKeypad = Keyboard();
char buf[BUFFER_SIZE];
char bufIndex = 0;


void resetBuffer() {
  memset(buf,0,BUFFER_SIZE);
  bufIndex = 0;
}


void setup() {
  //initMotor();
  //gotoFreq(maxFreq);

  resetBuffer();

  Wire.begin(0x12);  // https://github.com/mchobby/I2C_Intro/tree/master/01_MasterReader/MasterReader_Esclave
  Wire.onRequest(requestEvent);
}

void requestEvent()
{
  Wire.write(buf);
  resetBuffer();
}



void loop() {

  char customKey = customKeypad.getKey();
  
  if ((customKey) && (bufIndex < BUFFER_SIZE - 1)){
    buf[bufIndex++] = customKey;
  }
}
