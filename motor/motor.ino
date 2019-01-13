
#include "motor.h"
#include "keyboard.h"

int maxFreq = 65000;

Keyboard customKeypad = Keyboard();
String data = String();


void setup() {
  //initMotor();
  //gotoFreq(maxFreq);

  Serial.begin(9600);
}



void loop() {

  char customKey = customKeypad.getKey();
  
  if (customKey){
    data = data + String(customKey);
    Serial.println(data);
  }
}
