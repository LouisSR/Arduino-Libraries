/*
  Utils.h : Miscellaneous functions
  Created by Louis SR, November 20, 2015.
  Released into the public domain.
*/
#ifndef Utils_h
#define Utils_h

#define MAX_VOLTAGE 93 //MAX_VOLTAGE = 5V x (R1+R2)/R2 x 10

int batteryVoltage(int pin);
int photoCell(int pin);
int pir(int pin);

#endif