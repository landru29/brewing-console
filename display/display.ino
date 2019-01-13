
#include "screen.h"
#include "temperature.h"

Screen display = Screen();

void setup() {
  Serial.begin(9600);

  display.init();
  
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  display.setTextSize(0); 
  display.setTextColor(WHITE, BLACK); 
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
  delay(1000);
}
