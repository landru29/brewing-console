
#include "keyboard.h"
#include "screen.h"


String data = String();
Keyboard customKeypad = Keyboard();
Screen display = Screen();

void setup() {

  display.init();
  

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(0); 
  display.setCursor(0,0);
  display.setTextColor(WHITE, BLACK); 
  display.println("Hello, world!");
  display.display();

  
}

void loop() {
  
  char customKey = customKeypad.getKey();
  
  if (customKey){
    data = data + String(customKey);
    display.setCursor(0,8);
    display.println(data);
    display.display();
    
  }
}
