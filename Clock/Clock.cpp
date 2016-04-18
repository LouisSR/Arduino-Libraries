/*
  Clock.cpp - Library for measuring the computational time of a function.
  Created by Louis SR, March 2016.
*/

#include "Clock.h"

Clock::Clock(void)
{
}

void Clock::begin(unsigned int interval_ms)
{
	start();
	_toc = _tic;
	_interval_us = ((unsigned long) interval_ms) * 1000;
}

void Clock::start(void)
{
	_tic = micros();
}

void Clock::stop(void)
{
	_toc = micros();
}

unsigned long Clock::elapsedTime(void)
/** Return time elapsed between start and either 
last stop or now if stop is outdated **/
{
	if(_toc < _tic)
	{
		stop();
	}
	return(_toc - _tic);
}

bool Clock::isItTime(void)
/** Return true if time is elapsed. Return false if not **/
{
	unsigned long elapsedTime = micros() - _tic;
	bool status;

	if(elapsedTime > _interval_us)
	{
		status = true;
		start(); // reset the clock
	}
	else
	{
		status = false;
	}
	return status;
}

bool Clock::wait(void)
/** Wait until time between now and start is 
equal to interval_ms 
Return True if it was needed to wait
**/
{
	bool waited;
	unsigned long timeToStop;
	unsigned long timeElapsed;

	stop();

	timeElapsed = _toc - _tic;

	if( _interval_us > timeElapsed )
	{
		timeToStop = _interval_us - timeElapsed;
		if( timeToStop > 16000) //Arduino.cc: "Currently, the largest value that will produce an accurate delay is 16383"
		{
			// it uses delayMicroseconds() for the last 5ms because it is more precise
			delay( (timeToStop)/1000 - 5 ) ;
			stop();
			timeElapsed = _toc - _tic;
			timeToStop = _interval_us - timeElapsed;
			delayMicroseconds(timeToStop-30);
		}
		else
		{
			delayMicroseconds(timeToStop-10);
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
