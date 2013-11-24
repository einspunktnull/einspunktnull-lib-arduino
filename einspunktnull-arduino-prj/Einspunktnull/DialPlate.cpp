/*
 *  DialPlate.cpp - Library for use with DialPlates.
 *  Created by Albrecht Nitsche, October 22, 2010.
 *  Released into the public domain.
 */

#include "Arduino.h"
#include "DialPlate.h"

#define LENGTH 16

int _rufNr[LENGTH];

DialPlate::DialPlate(int dialPin, int impulsePin, int resetPin, int impulseTime)
{
	_dialPin = dialPin;
	_impulsePin = impulsePin;
	_resetPin = resetPin;
	_impulseTime = impulseTime;
	_rufNrIndex = 0;
	
	pinMode(_dialPin, INPUT);
    pinMode(_impulsePin, INPUT); 
    pinMode(_resetPin, INPUT); 
	reset();
}


bool DialPlate::isDialing()
{
	if(digitalRead(_resetPin))
	{
		reset();
		return false;
	}
	else
	{
		int zahl = getNumber();
		if(zahl>=0)
		{
			_rufNr[_rufNrIndex] = zahl;
			_rufNrIndex++;
		  
			for (int j = 0;j<LENGTH;j++)
			{
				Serial.print(_rufNr[j]);
				Serial.print(" ");
			}
			Serial.println(); 
		}
		return true;
	}
}

void DialPlate::reset()
{
	for (int j = 0;j<LENGTH;j++)_rufNr[j]=-1;
    _rufNrIndex = 0;
}

int DialPlate::getNumber()
{
	int c=0;
	while(digitalRead(_dialPin))
	{
		if(!digitalRead(_impulsePin))
		{
			c++;
			delay(_impulseTime);
		}   
	}
	if (c==0 || c>10)return -1;
	else if (c == 10)return 0;
	else return c;
}




