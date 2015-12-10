/*
  Utils.h : Miscellaneous functions
  Created by Louis SR, November 20, 2015.
  Released into the public domain.
*/
#ifndef Utils_h
#define Utils_h

#include <Arduino.h>

#define MAX_VOLTAGE 93 //MAX_VOLTAGE = 5V x (R1+R2)/R2 x 10
#define MAX_LUMINOSITY 100
#define MAX_ADC 1023

uint8_t batteryVoltage(uint8_t pin);
uint8_t photoCell(uint8_t pin);
boolean pir(uint8_t pin);

#endif