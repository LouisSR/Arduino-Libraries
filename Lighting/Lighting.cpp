/*
	Ligthing.h - Library for lightings.
	Created by Louis SR, April 3, 2016.
	Released into the public domain.
*/

#include "Lighting.h"

const byte lightThreshold = 20;
const byte lightHysteresis = 2;

Lighting::Lighting(void)
{
}

void Lighting::begin(byte positionLamp, byte reversingLamp, byte stopLamp , byte luminosityPin)
{
	_positionLamp = positionLamp;
	_reversingLamp = reversingLamp;
	_stopLamp = stopLamp;
	_luminosityPin = luminosityPin;
	pinMode(_positionLamp, OUTPUT); 
	pinMode(_reversingLamp, OUTPUT);
	pinMode(_stopLamp, OUTPUT);
	pinMode(_luminosityPin, INPUT);
	digitalWrite(_positionLamp, LOW);
}

void Lighting::update(byte state)
{
	byte luminosity;
	digitalWrite(_stopLamp, LOW);
	digitalWrite(_reversingLamp, LOW);

	//check car state
	if(state == REVERSE)
	{
		digitalWrite(_reversingLamp, HIGH);
	}
	else if (state == BRAKING)
	{
		digitalWrite(_stopLamp, HIGH);
	}

	//check luminosity
	luminosity = photoCell(_luminosityPin);
	if ( luminosity < lightThreshold - lightHysteresis )
	{
		digitalWrite(_positionLamp, HIGH);
	}
	else if (luminosity > lightThreshold + lightHysteresis)
	{
		digitalWrite(_positionLamp, LOW);
	}
	
}
