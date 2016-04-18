/*

  Created by Louis SR, November 20, 2015.
  Released into the public domain.
*/

#include <Arduino.h>
#include "Utils.h"

uint8_t batteryVoltage(uint8_t pin, uint8_t led)
{
	int adc;
	uint8_t voltage;

	adc = analogRead(pin);
	voltage = (uint8_t) map(adc,0,MAX_ADC,0,MAX_VOLTAGE);

	//if battery low, turn on led
	if(voltage < VOLTAGE_THRESHOLD)
	{
		digitalWrite(led, HIGH);
	}
	else
	{
		digitalWrite(led, LOW);
	}

	return voltage;
}

uint8_t photoCell(uint8_t pin)
{
	int adc;
	uint8_t luminosity;
	adc = analogRead(pin);
	luminosity = (uint8_t) map(adc,0,MAX_ADC,0,MAX_LUMINOSITY);
	Serial.println(luminosity);
	return luminosity;
}

bool pir(uint8_t pin) 
{
	int pirReading = digitalRead(pin);

	if(pirReading > MAX_ADC/2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void printUnsigned(const char* name, unsigned long data)
{
	Serial.print(name);
	Serial.print(": ");
	Serial.println(data); 
}
void printSigned(const char* name, long data)
{
	Serial.print(name);
	Serial.print(": ");
	Serial.println(data); 
}
void printFloat(const char* name, float data)
{
	Serial.print(name);
	Serial.print(": ");
	Serial.println(data); 
}