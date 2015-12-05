/*
	Schedule.h - Library for scheduling fonctions.
	Created by Louis SR, December 5, 2015.
	Released into the public domain.
*/

#ifndef Schedule_h
#define Schedule_h

#include "Arduino.h"

class Schedule
{
	public:
		Schedule(unsigned long interval);
		void begin(void);
		boolean isItTime(void);
		void call(void);
	
	private:
		unsigned long _lastCall;
		unsigned long _interval;
};

#endif