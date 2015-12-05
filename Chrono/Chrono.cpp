/*
  Chrono.cpp - Library for measuring the computational time of a function.
  Created by Louis SR, December 5, 2015.
  Released into the public domain.
*/

#include "Chrono.h"


Chrono::Chrono(char* name, unsigned int interval)
{
	for(byte letter=0;letter<11;letter++)
	{
		_name[letter] = name[letter];
	}
	_tic = 0;
	_toc = 0;
	_interval = ((unsigned long) interval) * 1000;
}

void Chrono::begin(void)
{
	start();
}

void Chrono::start(void)
{
	_tic = micros();
}

void Chrono::stop(void)
{
	_toc = micros() - _tic;
}

unsigned long Chrono::elapsedTime(void)
{
	return(_toc);
}

void Chrono::wait(void)
{
	stop();

	if( _interval > _toc)
	{
		unsigned long timeToStop = _interval - _toc;
		if (timeToStop > 65000)
		{
			delay(timeToStop/1000);
		}
		else
		{
			delayMicroseconds(timeToStop);
		}
	}

	start();
}

void Chrono::display(void)
{
	Serial.print(" Time of ");
	Serial.print(_name);
	Serial.print(": ");
	Serial.print(_toc); 
	Serial.println(" us");
}