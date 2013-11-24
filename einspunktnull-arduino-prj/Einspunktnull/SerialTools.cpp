/*
 SerialTools.cpp - Library for use with Serial.
 Created by Albrecht Nitsche, October 20, 2010.
 Released into the public domain.
 */

#include "Arduino.h"
#include "SerialTools.h"

SerialTools::SerialTools(int bufferSize, int delay)
{
	_bufferSize = bufferSize;
	_delay = delay;
}

String SerialTools::getSerialString()
{
	char serialReadBuffer[_bufferSize];
	for (int i = 0; i < _bufferSize; i++)
		serialReadBuffer[i] = NULL;
	int index = 0;
	if (Serial.available())
	{
		while (Serial.available())
		{
			serialReadBuffer[index++] = Serial.read();
			delay(_delay);//wait between single chars
		}
	}
	return String(serialReadBuffer);
}

