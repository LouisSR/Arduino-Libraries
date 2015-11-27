/*

  Created by Louis SR, November 20, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Utils.h"

int batteryVoltage(int pin)
{
	int adc, voltage;
	adc = analogRead(pin);
	voltage = map(adc,0,1023,0,MAX_VOLTAGE);
	return voltage;
}

int photoCell(int pin)
{
	int adc = analogRead(pin);
	return adc;
}

int pir(int pin)
{
	int pirReading = digitalRead(pin);
	return pirReading;
}