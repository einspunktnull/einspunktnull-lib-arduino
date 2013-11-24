/*
 SerialTools.h - Library for use with Serial.
 Created by Albrecht Nitsche, October 20, 2010.
 Released into the public domain.
 */
#ifndef SerialTools_h
#define SerialTools_h

#include "Arduino.h"

class SerialTools
{
	public:
		SerialTools(int bufferSize, int delay);
		String getSerialString();
	private:
		int _bufferSize;
		int _delay;
};

#endif

