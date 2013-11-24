#ifndef SAAPREDFLY_H_
#define SAAPREDFLY_H_

#include <RedFly.h>
#include "SAAP.h"

class SAAPRedFly:public SAAP
{
	private:
		uint8_t _http;//socket handle
		bool _listening;
		String _ssid;
		String _pwd;


	public:
		SAAPRedFly();
		void initialize(ErrorFunctionPointer errorFctPtr, HardwareSerial *debugSerialPtr, String ssid, String pwd);
		void receive();
};

#endif
