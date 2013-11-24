#include "SAAPMessage.h"
#include <HardwareSerial.h>


/*************************************************
 * PUBLIC
 *************************************************/
SAAPMessage::SAAPMessage()
{
	init();
}

int SAAPMessage::setBytes(uint8_t *bytes)
{
	for (int i = 0; i < _length; i++)
	{
		bytes[i] = _bytesBuffer[i];
	}
	return _length;
}

void SAAPMessage::append(uint8_t data)
{
	_bytesBuffer[_length] = data;
	_length += 1;
}

void SAAPMessage::append(const String& data)
{
	int len = data.length();
	char buf[len + 1];
	data.toCharArray(buf, len + 1);
	for (int i = 0; i < len; i++)
	{
		_bytesBuffer[_length + i] = buf[i];
	}
	_length += len;
}

/*************************************************
 * PRIVATE
 *************************************************/
void SAAPMessage::init()
{
	_length = 0;
}

