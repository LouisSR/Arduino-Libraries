/*
	Chronos.h - Library for measuring the computational time of a function.
	Created by Louis SR, December 5, 2015.
*/

#ifndef Chronos_h
#define Chronos_h

#include <Arduino.h>

class Chronos
{
	public:
		Chronos(unsigned int interval_ms=0);
		void begin(unsigned int interval_ms=0);
		void start(void);
		void stop(void);
		unsigned long elapsedTime(void);
		bool wait(void);
	
	private:
		unsigned long _tic;
		unsigned long _toc;
		unsigned long _interval_us;
};

#endif