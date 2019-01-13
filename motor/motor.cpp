#include "motor.h"

unsigned int microseconds = 600;
unsigned int timer1_counter;
unsigned int frequencyHz;
unsigned int targetHz;
int stable;

unsigned int getPreload() {
  double f = (double)frequencyHz / 1000;
  unsigned int sub = (int) ((double)FREQ / f);
  // preload: 65535 - 16000000 / (prescale * freq)
  return 65535 - sub;
}

void stepFrequency() {
  unsigned int pitch = abs(frequencyHz-targetHz) < PITCH ? abs(frequencyHz-targetHz) : PITCH;
  if (frequencyHz < targetHz) {
    frequencyHz += pitch;
  }
  if (frequencyHz > targetHz) {
    frequencyHz -= pitch;
  }
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  stable--;
  if (stable<=0) {
    stable = frequencyHz / 50;
    stepFrequency();
  }
  TCNT1 = getPreload();   // preload timer
  digitalWrite(PLS, digitalRead(PLS) ^ 1);
}

void setFrequency (unsigned int hz) {
  frequencyHz = hz;
  targetHz = hz;
  stable = hz / 50;
  TCNT1 = getPreload();
}

void timerSetup () {
   noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  
  setFrequency(5000);
  TCCR1B |= (1 << CS10);    // no prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();         
}

void gotoFreq(unsigned int f) {
  targetHz = f;
}

void initMotor() {
  pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(PLS, OUTPUT);
  digitalWrite(ENA, HIGH);
  digitalWrite(DIR, HIGH);
  digitalWrite(PLS, HIGH);
  delay(500);
  timerSetup ();
}
