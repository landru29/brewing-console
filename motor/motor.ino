
#include "motor.h"
#include "keyboard.h"
#include "string.h"
#include <Wire.h>

#define BUFFER_SIZE 20

float maxFreq = 65000.0;
float minFreq = 5000.0;
float currentFreq = minFreq;

Keyboard customKeypad = Keyboard();
char buf[BUFFER_SIZE];
char bufIndex = 0;


void resetBuffer() {
  memset(buf,0,BUFFER_SIZE);
  bufIndex = 0;
}


void setup() {
  initMotor();
  gotoFreq(currentFreq);

  resetBuffer();

  Wire.begin(0x12);  // https://github.com/mchobby/I2C_Intro/tree/master/01_MasterReader/MasterReader_Esclave
  Wire.onRequest(requestEvent);
}

void requestEvent()
{
  Wire.write(buf);
  resetBuffer();
}


void setMaxSpeed() {
  currentFreq = maxFreq;
  setEnable(true);
  gotoFreq(currentFreq);
}

void stopMotor() {
  currentFreq = minFreq;
  setEnable(false);
  setFrequency(currentFreq);
}

void increaseSpeed() {
  currentFreq *= 1.2;
  if (currentFreq > maxFreq) {
    currentFreq = maxFreq;
  }
  setEnable(true);
  gotoFreq(currentFreq);
}

void decreaseSpeed() {
  currentFreq /= 1.2;
  setEnable(true);
  if (currentFreq < minFreq) {
    currentFreq = minFreq;
  }
  gotoFreq(currentFreq);
}

void loop() {

  char customKey = customKeypad.getKey();
  
  if ((customKey) && (bufIndex < BUFFER_SIZE - 1)){

    switch(customKey) {
      case 'A':
        setMaxSpeed();
        break;
      case 'B':
        increaseSpeed();
        break;
      case 'C':
        decreaseSpeed();
        break;
      case 'D':
        stopMotor();
        break;
      default:
        buf[bufIndex++] = customKey;
    }
  }
}
