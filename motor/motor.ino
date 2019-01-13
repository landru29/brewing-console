
#include "motor.h"
#include "keyboard.h"
#include "string.h"
#include <Wire.h>

#define BUFFER_SIZE 20

int maxFreq = 65000;

Keyboard customKeypad = Keyboard();
String data = String();


void setup() {
  //initMotor();
  //gotoFreq(maxFreq);

  Wire.begin(0x12);  // https://github.com/mchobby/I2C_Intro/tree/master/01_MasterReader/MasterReader_Esclave
  Wire.onRequest(requestEvent);
}

void requestEvent()
{
  char buf[BUFFER_SIZE];
  memset(buf,0,BUFFER_SIZE);
  data.toCharArray(buf, BUFFER_SIZE);
  data = String();
  Wire.write(buf); 
}



void loop() {

  char customKey = customKeypad.getKey();
  
  if (customKey){
    data = data + String(customKey);
  }
}
