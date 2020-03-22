
#include "screen.h"
#include "temperature.h"

#define PRE_LOAD 312500

int minutes = 0;
int seconds = 0;
int hours = 0;
bool busy = false;
int currentTemp = 0;

Screen display = Screen();

void tick() {
  char data[10];
  display.setTextSize(0); 
  display.setCursor(5, 24);
  sprintf(data, "%02d:%02d:%02d", hours, minutes, seconds);
  display.print(data);
  display.display();
}

void /*ICACHE_RAM_ATTR*/ onTimerISR() {
  if ((++seconds) > 59) {
    seconds = 0;
    if (++minutes > 59) {
      minutes = 0;
      hours++;
    }
  }

  if (!busy) {
    busy = true;
    tick();
    busy = false;
  }
}

void initTemperature() {
  Temperature::searchSensors();
}

void setup() {
  Wire.begin(); 
  Serial.begin(9600);

initTemperature();
  
  display.init();
  
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(WHITE, BLACK); 
  display.display();

  // Initialize Ticker every 0.5s
  /*timer1_attachInterrupt(onTimerISR);
  timer1_enable(3, TIM_EDGE, TIM_LOOP);
  timer1_write(PRE_LOAD); // 120000 µs*/
}

void readKeyboard() {
  Wire.requestFrom(0X12, 20);

  char data[20];
  char i = 0;
  while(Wire.available())
  {
    unsigned char c = Wire.read();
    data[i++] = (c == 0xFF ? 0 : c);

    if ((c>='1') && (c<='9')) {
      currentTemp = c-'1';
      display.setTextSize(0);
      display.setCursor(0,0);
      display.println(String("Capteur ") + (currentTemp + 1));
    }
    
  }
  //display.setTextSize(0);
  //display.clearLine(0);
  //display.setCursor(0, 0);
  //display.println(data);
  //display.display();
}

void loop() {
  display.setTextSize(0);
  display.setCursor(0,0);
  display.println(String("Capteur ") + (currentTemp + 1));
  
  if (Temperature::count) {
    float celcius = Temperature::sensor[currentTemp]->performMeasure();
    Serial.println(celcius);
    display.setTextSize(2);
    
    display.setCursor(0,8);
    display.println("         ");
    
    display.setCursor(8,8);
    display.println(String(celcius));
    display.display();

  } else {
    display.print("No sensor     ");
  }

  readKeyboard();
  
  delay(500);
}
