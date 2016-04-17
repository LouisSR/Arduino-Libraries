/*
	Ligthing.h - Library for lightings.
	Created by Louis SR, April 3, 2016.
	Released into the public domain.
*/
#ifndef Lighting_h
#define Lighting_h

#include <Arduino.h>
#include "Utils.h"

#define BRAKING	2
#define REVERSE	3

class Lighting
{
	public:
		Lighting(void);
		void begin(byte positionLamp, byte reversingLamp, byte stopLamp, byte luminosityPin);
		void update(byte state);
	private:
		byte _positionLamp;
		byte _reversingLamp;
		byte _stopLamp;
		byte _luminosityPin;
};

#endif