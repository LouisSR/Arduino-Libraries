/*
	Clock.h - Library for measuring the computational time of a function.
	Created by Louis SR, March 2016
*/

#ifndef Clock_h
#define Clock_h

#include <Arduino.h>

class Clock
{
	public:
		Clock(void);
		void begin(unsigned int interval_ms=0);
		void start(void);
		void stop(void);
		unsigned long elapsedTime(void);
		bool wait(void);
		bool isItTime(void);
	
	private:
		unsigned long _tic;
		unsigned long _toc;
		unsigned long _interval_us;
};

#endif