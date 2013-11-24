/*
 AndroduinoBluetooth.h - Arduino Library for AndroduinoBluetooth
 Copyright (c) 2012 Albrecht Nitsche.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Acknowledgements:
 This library is based on the MeetAndroid library from Bonifaz Kaufmann's Amarino Toolkit (http://www.amarino-toolkit.net/).
 The original library has been modified to address the
 specific demand to communicate with the AndroduinoBluetooth based Software.

 Website:
 http://einspunktnull.net

 last modified by Albrecht Nitsche 19th July 2012
 */

#ifndef Androduino_h
#define Androduino_h

#include <inttypes.h>
#include "Print.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

class AndroduinoBluetooth: public Print {

private:

	const static uint8_t BYTE_BUFFER_SIZE = 64;
	const static uint8_t BYTE_BUFFER_WAIT_TIME = 30;
	const static uint8_t FUNCTION_BUFFER_SIZE = 128; // 48-122 (in ascii: 0 - z)

	const static char BYTE_START = 0x11; //(DC1 - device control 1);
	const static char BYTE_BREAK = 0x12; //(DC2 - device control 2);
	const static char BYTE_END = 0x13; //(DC3 - device control 3);
	const static char BYTE_DELIM = 0x14; //(DC4 - device control 4);

	uint8_t _buffer[BYTE_BUFFER_SIZE];
	uint8_t _count;
	int _numValues;

	void handleMessage(void);
	int getArrayLength(void);
public:
	AndroduinoBluetooth(void);
	bool receive(void);
	void flush(void);
	void getBuffer(uint8_t[]);

	void registerFunction(void (*)(uint8_t, uint8_t), uint8_t);
	void unregisterFunction(uint8_t);

	typedef void (*H_voidFuncPtr)(uint8_t, uint8_t);
	H_voidFuncPtr _intFunc[FUNCTION_BUFFER_SIZE];
	H_voidFuncPtr _errorFunc;

	size_t write(uint8_t);

	uint8_t getByte();
	void getString(char[]);
	long getLong();

	int getInt();
	int getIntAt(int);
	void getIntValues(int[]);

	float getFloat();
	float getFloatAt(int);
	void getFloatValues(float[]);

	double getDouble();
	double getDoubleAt(int);
	void getDoubleValues(float[]); // in Arduino double and float are the same

	void send(char);
	void send(char, char);
	void send(char, const char[]);
	void send(char, uint8_t);
	void send(char, int);
	void send(char, unsigned int);
	void send(char, long);
	void send(char, unsigned long);
	void send(char, double);
	void sendln(void);
};

// Arduino 0012 workaround
#undef int
#undef char
#undef long
#undef byte
#undef float
#undef abs
#undef round

#endif

