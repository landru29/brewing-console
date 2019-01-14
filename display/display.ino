
#include "screen.h"
#include "temperature.h"

Screen display = Screen();

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  display.init();
  
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  display.setTextSize(0); 
  display.setTextColor(WHITE, BLACK); 
  display.display();
}

void readKeyboard() {
  Wire.requestFrom(0X12, 20);

  char data[20];
  char i = 0;
  while(Wire.available())
  {
    unsigned char c = Wire.read();
    data[i++] = (c == 0xFF ? 0 : c);
    
  }
  display.clearLine(8);
  display.setCursor(0, 8);
  display.println(data);
  display.display();
}

void loop() {
  
  if (getAddress()) {
    float celcius = performMeasure();
    display.setCursor(8,0);
    display.println(String(celcius));
    display.display();

  } else {
    display.print(" xx.xx ");
  }

  readKeyboard();
  
  delay(1000);
}
