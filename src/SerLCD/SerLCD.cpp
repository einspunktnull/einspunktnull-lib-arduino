#include <Arduino.h>
#include "SerLCD.h"

SerLCD::SerLCD()
{
}

void SerLCD::begin(HardwareSerial *serialPtr, long baudrate)
{
	_serialPointer = serialPtr;
	serialPtr->begin(baudrate);
}

void SerLCD::print(String str)
{
	_serialPointer->write(0xFE);
	_serialPointer->write(0x01);
	_serialPointer->print(str);
}

