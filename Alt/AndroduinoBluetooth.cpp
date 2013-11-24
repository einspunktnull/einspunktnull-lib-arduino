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

 
/*
 
#include "Arduino.h"
#include "AndroduinoBluetooth.h"

extern "C" {
#include <stdlib.h>
}

/******************************************************************************
 * PUBLIC GENERAL
 ******************************************************************************/

AndroduinoBluetooth::AndroduinoBluetooth() {
	_count = 0;
	_numValues = 0;
	for (int a = 0; a < FUNCTION_BUFFER_SIZE; a++) {
		_intFunc[a] = _errorFunc;
	}
}

bool AndroduinoBluetooth::receive() {
	uint8_t byte;
	boolean timeout = false;
	while (!timeout) {
		while (Serial.available() > 0) {
			byte = Serial.read();
			if (byte == BYTE_BREAK) {
				flush();
			} else if (byte == BYTE_END) {
				handleMessage();
				flush();
			} else if (_count < BYTE_BUFFER_SIZE) {
				_buffer[_count] = byte;
				_count++;
			} else {
				return false;
			}
		}

		if (Serial.available() <= 0 && !timeout) {
			if (BYTE_BUFFER_WAIT_TIME > 0)
				delayMicroseconds(BYTE_BUFFER_WAIT_TIME);
			if (Serial.available() <= 0)
				timeout = true;
		}
	}
	return timeout;
}

void AndroduinoBluetooth::flush() {
	for (uint8_t a = 0; a < BYTE_BUFFER_SIZE; a++) {
		_buffer[a] = 0;
	}
	_count = 0;
	_numValues = 0;
}

void AndroduinoBluetooth::getBuffer(uint8_t buf[]) {

	for (int a = 0; a < _count; a++) {
		buf[a] = _buffer[a];
	}
}

void AndroduinoBluetooth::registerFunction(
		void (*userfunction)(uint8_t, uint8_t), uint8_t command) {
	_intFunc[command] = userfunction;
}
void AndroduinoBluetooth::unregisterFunction(uint8_t command) {
	_intFunc[command] = _errorFunc;
}

size_t AndroduinoBluetooth::write(uint8_t b) {
	return Serial.write(b);
}

/******************************************************************************
 * PUBLIC GETTER
 ******************************************************************************/

int AndroduinoBluetooth::getInt() {
	uint8_t b[_count];
	for (int a = 1; a < _count; a++) {
		b[a - 1] = _buffer[a];
	}

	b[_count - 1] = '\0';
	return atoi((char*) b);
}

int AndroduinoBluetooth::getIntAt(int idx) {
	int values[BYTE_BUFFER_SIZE];
	getIntValues(values);
	return values[idx];
}

void AndroduinoBluetooth::getIntValues(int values[]) {
	int t = 0; // counter for each char based array
	int pos = 0;

	int start = 1; // start of first value
	for (int end = 1; end < _count; end++) {
		// find end of value
		if (_buffer[end] == BYTE_DELIM) {
			// now we know start and end of a value
			char b[(end - start) + 1]; // create container for one value plus '\0'
			t = 0;
			for (int i = start; i < end; i++) {
				b[t++] = (char) _buffer[i];
			}
			b[t] = '\0';
			values[pos++] = atoi(b);
			start = end + 1;
		}
	}
	// get the last value
	char b[(_count - start) + 1]; // create container for one value plus '\0'
	t = 0;
	for (int i = start; i < _count; i++) {
		b[t++] = (char) _buffer[i];
	}
	b[t] = '\0';
	values[pos] = atoi(b);
}

float AndroduinoBluetooth::getFloat() {
	return (float) getDouble();
}

float AndroduinoBluetooth::getFloatAt(int idx) {
	float values[BYTE_BUFFER_SIZE];
	getFloatValues(values);
	return values[idx];
}

void AndroduinoBluetooth::getFloatValues(float values[]) {
	int t = 0; // counter for each char based array
	int pos = 0;

	int start = 1; // start of first value
	for (int end = 1; end < _count; end++) {
		// find end of value
		if (_buffer[end] == BYTE_DELIM) {
			// now we know start and end of a value
			char b[(end - start) + 1]; // create container for one value plus '\0'
			t = 0;
			for (int i = start; i < end; i++) {
				b[t++] = (char) _buffer[i];
			}
			b[t] = '\0';
			values[pos++] = atof(b);
			start = end + 1;
		}
	}
	// get the last value
	char b[(_count - start) + 1]; // create container for one value plus '\0'
	t = 0;
	for (int i = start; i < _count; i++) {
		b[t++] = (char) _buffer[i];
	}
	b[t] = '\0';
	values[pos] = atof(b);
}

double AndroduinoBluetooth::getDouble() {
	char b[_count];
	for (int a = 1; a < _count; a++) {
		b[a - 1] = (char) _buffer[a];
	}

	b[_count - 1] = '\0';
	return atof(b);
}

double AndroduinoBluetooth::getDoubleAt(int idx) {
	return getFloatAt(idx);
}

void AndroduinoBluetooth::getDoubleValues(float values[]) {
	getFloatValues(values);
}

uint8_t AndroduinoBluetooth::getByte() {
	return _buffer[1];
}

void AndroduinoBluetooth::getString(char string[]) {

	for (int a = 1; a < _count; a++) {
		string[a - 1] = _buffer[a];
	}
	string[_count - 1] = '\0';
}

long AndroduinoBluetooth::getLong() {
	uint8_t b[_count];
	for (int a = 1; a < _count; a++) {
		b[a - 1] = _buffer[a];
	}

	b[_count - 1] = '\0';
	return atol((char*) b);
}

/******************************************************************************
 * PUBLIC SEND
 ******************************************************************************/
void AndroduinoBluetooth::send(char flag) {
	Serial.write(flag);
	Serial.write(BYTE_END);
}

void AndroduinoBluetooth::send(char flag, char val) {
	Serial.write(flag);
	Serial.write(val);
	Serial.write(BYTE_END);
}

void AndroduinoBluetooth::send(char flag, const char str[]) {
	Serial.write(flag);
	Serial.write(str);
	Serial.write(BYTE_END);
}
void AndroduinoBluetooth::send(char flag, uint8_t n) {
	Serial.write(flag);
	Serial.write(n);
	Serial.write(BYTE_END);
}
void AndroduinoBluetooth::send(char flag, int n) {
	Serial.write(flag);
	Serial.write(n);
	Serial.write(BYTE_END);
}
void AndroduinoBluetooth::send(char flag, unsigned int n) {
	Serial.write(flag);
	Serial.write(n);
	Serial.write(BYTE_END);
}
void AndroduinoBluetooth::send(char flag, long n) {
	Serial.write(flag);
	Serial.write(n);
	Serial.write(BYTE_END);
}
void AndroduinoBluetooth::send(char flag, unsigned long n) {
	Serial.write(flag);
	Serial.write(n);
	Serial.write(BYTE_END);
}

void AndroduinoBluetooth::send(char flag, double n) {
	Serial.write(flag);
	Serial.write(n);
	Serial.write(BYTE_END);
}

void AndroduinoBluetooth::sendln(void) {
	char lf = 0x0A;
	Serial.write(lf);
	Serial.write(BYTE_END);
}

/******************************************************************************
 * PRIVATE
 ******************************************************************************/
int AndroduinoBluetooth::getArrayLength() {
	if (_count == 1)
		return 0;
	_numValues = 1;
	for (int a = 1; a < _count; a++) {
		if (_buffer[a] == BYTE_DELIM)
			_numValues++;
	}
	return _numValues;
}

void AndroduinoBluetooth::handleMessage() {
	char flag = _buffer[0];
	void (*H_FuncPtr)(uint8_t, uint8_t) = _intFunc[flag];
	if (H_FuncPtr != 0) {
		H_FuncPtr(flag, getArrayLength());
	}
}

*/