#include "SAAP.h"

SAAP::SAAP()
{
}

void SAAP::initialize(ErrorFunctionPointer errorFctPtr, HardwareSerial *debugSerialPtr)
{
	_debugSerialPtr = debugSerialPtr;
	_debugSerialPtr->begin(9600);

	_errorFctPtr = errorFctPtr;

	for (int a = 0; a < FUNCTION_BUFFER_SIZE; a++)
	{
		_functionPointers[a] = 0;
		_functionNumArguments[a] = 0;
	}

}

void SAAP::onByteReceived(uint8_t byte)
{
	_debugSerialPtr->print((char) byte);
	_buffer[_count] = byte;
	_count++;

	if (byte == BYTE_END)
	{
		countArguments();
		handleCommand(true);
		flush();
	}
}

void SAAP::flush()
{
	for (uint8_t i = 0; i < BUFFER_SIZE; i++)
	{
		_buffer[i] = 0;
	}
	_count = 0;
	_numValues = 0;
	_position = 1;
}

void SAAP::countArguments()
{
	for (uint8_t i = 0; i < _count; i++)
	{
		uint8_t byte = _buffer[i];

		if (byte == BYTE_DELIMITER)
		{
			_numValues++;
		}
	}
	if (_numValues == 0 && _count > 2) _numValues = 1;
	else if (_numValues > 0) _numValues++;
}

void SAAP::handleCommand(const bool msgComplete)
{
	if (!msgComplete)
	{
		_debugSerialPtr->print("incomplete Message > Timeout");
		if (_errorFctPtr != 0) _errorFctPtr(1, '!', 0);
		else onError(1, '!', 0);
		return;
	}

	//get CommandChar from buffer
	uint8_t command = _buffer[0];
	uint8_t idx = command - FUNCTION_BUFFER_OFFSET;

	//is command valid (ASCII-range 48-122)
	bool isValidCommand = command >= FUNCTION_BUFFER_OFFSET && command <= 122;
	if (!isValidCommand)
	{
		_debugSerialPtr->print("invalidCommand");
		if (_errorFctPtr != 0) _errorFctPtr(2, '!', 0);
		else onError(2, '!', 0);
		return;
	}

	//is command registered
	void (*FunctionPointer)(const uint8_t errorNum, const uint8_t command, const uint8_t numValues) = _functionPointers[idx];
	bool isRegisteredCommand = FunctionPointer != 0;
	if (!isRegisteredCommand)
	{
		_debugSerialPtr->print("unregisteredCommand");
		if (_errorFctPtr != 0) _errorFctPtr(3, '!', 0);
		else onError(3, '!', 0);
		return;
	}

	//correct number of arguments ?
	uint8_t numArguments = _functionNumArguments[idx];
	bool isCorrectArgumentNum = _numValues == numArguments;
	if (!isCorrectArgumentNum)
	{
		_debugSerialPtr->print("invalidArgCount ");
		if (_errorFctPtr != 0) _errorFctPtr(4, '!', 0);
		else onError(4, '!', 0);
		return;
	}

	FunctionPointer(0, command, _numValues);

}

void SAAP::onError(const uint8_t errorNum, const uint8_t command, const uint8_t numValues)
{
	String origMsg = getMessage();
	String msgCopy = origMsg;
	msgCopy.replace(";", "#");
	msgCopy.replace(",", "'");
	String send = "!" + String(errorNum) + "," + msgCopy + ";";
	//_serialPointer->print(send);
	_debugSerialPtr->print(send);
}

String SAAP::getMessage()
{
	char txt[_count + 2];

	for (int pos = 0; pos < _count; pos++)
	{
		txt[pos] = _buffer[pos];
	}
	txt[_count] = '\0';

	String msg = String(txt);
	return msg;
}
