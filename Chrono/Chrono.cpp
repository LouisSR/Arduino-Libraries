/*
  Chrono.cpp - Library for measuring the computational time of a function.
  Created by Louis SR, December 5, 2015.
  Released into the public domain.
*/

#include "Chrono.h"

Chrono::Chrono(unsigned int interval_ms)
{
	_tic = 0;
	_toc = 0;
	_interval_us = ((unsigned long) interval_ms) * 1000;
}

void Chrono::start(void)
{
	_tic = micros();
}

void Chrono::stop(void)
{
	_toc = micros();
}

unsigned long Chrono::elapsedTime(void)
/** Return time elapsed between start and either 
last stop or now if stop is outdated **/
{
	if(_toc < _tic)
	{
		stop();
	}
	return(_toc - _tic);
}

void Chrono::wait(void)
/** Wait until time between start and now is 
equal to interval_ms **/
{
	stop();

	unsigned long timeElapsed = _toc - _tic;
	if( _interval_us > timeElapsed )
	{
		unsigned long timeToStop = _interval_us - timeElapsed;
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
