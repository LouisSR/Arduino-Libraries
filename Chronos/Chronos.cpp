/*
  Chronos.cpp - Library for measuring the computational time of a function.
  Created by Louis SR, December 5, 2015.
*/

#include "Chronos.h"

Chronos::Chronos(unsigned int interval_ms)
{
	_tic = 0;
	_toc = 0;
	_interval_us = ((unsigned long) interval_ms) * 1000;
}

void Chronos::begin(unsigned int interval_ms)
{
	_interval_us = ((unsigned long) interval_ms) * 1000;
}

void Chronos::start(void)
{
	_tic = micros();
}

void Chronos::stop(void)
{
	_toc = micros();
}

unsigned long Chronos::elapsedTime(void)
/** Return time elapsed between start and either 
last stop or now if stop is outdated **/
{
	if(_toc < _tic)
	{
		stop();
	}
	return(_toc - _tic);
}

bool Chronos::wait(void)
/** Wait until time between now and start is 
equal to interval_ms 
Return True if it neds to wait
**/
{
	bool waited;
	stop();

	unsigned long timeElapsed = _toc - _tic;
	if( _interval_us > timeElapsed )
	{
		unsigned long timeToStop = _interval_us - timeElapsed;
		if (timeToStop > 16000) //Arduino.cc: "Currently, the largest value that will produce an accurate delay is 16383"
		{
			delay(timeToStop/1000);
		}
		else
		{
			delayMicroseconds(timeToStop);
		}
		waited = true;
	}
	else
	{
		waited = false;
	}
	start();
	return waited;
}
