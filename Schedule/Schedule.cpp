/*
	Schedule.h - Library for scheduling fonctions.
	Created by Louis SR, December 5, 2015.
	Released into the public domain.
*/

#include "Schedule.h"

Schedule::Schedule(unsigned long interval)
{
	_lastCall = 0;
	_interval = interval;
}

void Schedule::begin(void)
{
	call();
}

boolean Schedule::isItTime(void)
{
	unsigned long elapsedTime = millis() - _lastCall;
	boolean status;

	if(elapsedTime > _interval)
	{
		status = true;
	}
	else
	{
		status = false;
	}
	return status;
}

void Schedule::call(void)
{
	_lastCall = millis();
}