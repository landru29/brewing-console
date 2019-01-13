#ifndef MOTOR_H
#define MOTOR_H

#include <inttypes.h>
#include <avr/interrupt.h>
#include "Arduino.h"

#define ENA 2
#define DIR 3
#define PLS 4
#define PITCH 700

#define FREQ 16000 //kHz



void gotoFreq(unsigned int f);
void initMotor();




#endif
