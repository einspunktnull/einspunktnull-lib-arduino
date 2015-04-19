#ifndef SERLCD_H_
#define SERLCD_H_

#include <HardwareSerial.h>


class SerLCD
{
	private:
		HardwareSerial *_serialPointer;
	public:
		SerLCD();
		void begin(HardwareSerial *serialPtr, long baudrate);
		void print(String str);

};

#endif
