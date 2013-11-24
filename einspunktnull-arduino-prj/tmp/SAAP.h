#ifndef SAAP_H_
#define SAAP_H_

#include <inttypes.h>
#include <WString.h>
#include <HardwareSerial.h>

const uint8_t BYTE_BREAK = '|';
const uint8_t BYTE_DELIMITER = ',';
const uint8_t BYTE_END = ';';
const static uint8_t BUFFER_SIZE = 64;

class SAAP
{
	private:

		// 48-122 (in ascii: 0 - z) a-z, A-Z, 0-9,
		const static uint8_t FUNCTION_BUFFER_SIZE = 75;
		const static uint8_t FUNCTION_BUFFER_OFFSET = 48;
		uint8_t _byteCommand;
		uint8_t _buffer[BUFFER_SIZE];
		uint8_t _count;
		uint8_t _numValues;
		uint8_t _position;

		typedef void (*FunctionPointer)(const uint8_t errorNum, const uint8_t command, const uint8_t numValues);
		FunctionPointer _functionPointers[FUNCTION_BUFFER_SIZE];
		uint8_t _functionNumArguments[FUNCTION_BUFFER_SIZE];


		void flush();
		void onError(const uint8_t errorNum, const uint8_t command, const uint8_t numValues);
		void handleCommand(const bool msgComplete);
		void countArguments();

	protected:
		SAAP();
		typedef void (*ErrorFunctionPointer)(const uint8_t errorNum, const uint8_t command, const uint8_t numValues);
		ErrorFunctionPointer _errorFctPtr;
		HardwareSerial *_debugSerialPtr;
		void initialize(ErrorFunctionPointer errorFctPtr, HardwareSerial *debugSerialPtr);
		void onByteReceived(uint8_t byte);

	public:
		void registerCommand(const uint8_t command, FunctionPointer fctPtr, const uint8_t numArguments);
		String getMessage();
		String getStringValue();
		int getIntValue();
		float getFloatValue();
		void send(String msg);
};

#endif
