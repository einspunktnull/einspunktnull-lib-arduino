/*
 * SAAPMessage.h
 *
 *  Created on: 27.06.2013
 *      Author: einspunktnull
 */

#ifndef SAAPMESSAGE_H_
#define SAAPMESSAGE_H_


#include <inttypes.h>
#include <WString.h>

class SAAPMessage
{
	private:
		void init(void);
		uint8_t _bytesBuffer[1024];
		int _length;

	public:

		SAAPMessage(void);

		void append(uint8_t);
		void append(const String&);
		int setBytes(uint8_t *);
};

#endif
