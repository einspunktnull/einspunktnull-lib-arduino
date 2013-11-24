#include "SAAPRedFly.h"

SAAPRedFly::SAAPRedFly()
{
}

void SAAPRedFly::initialize(ErrorFunctionPointer errorFctPtr, HardwareSerial *debugSerialPtr, String ssid, String pwd)
{
	SAAP::initialize(errorFctPtr, debugSerialPtr);

	_http = INVALID_SOCKET;
	_listening = false;

	_ssid = ssid;
	_pwd = pwd;

	_debugSerialPtr->println("setupRedflyAdapter");
	uint8_t result;
	_debugSerialPtr->print("REDFLY INIT");
	result = RedFly.init();
	if (result)
	{
		_debugSerialPtr->print("REDFLY INIT ERROR");
	}
	else
	{
		_debugSerialPtr->println("REDFLY SCAN");
		RedFly.scan();
		_debugSerialPtr->print("REDFLY JOIN: ");

		int len = ssid.length() + 1;
		char ssidArr[len];
		ssid.toCharArray(ssidArr, len);
		_debugSerialPtr->print(ssidArr);
		_debugSerialPtr->print(", ");

		len = pwd.length() + 1;
		char pwdArr[len];
		pwd.toCharArray(pwdArr, len);
		_debugSerialPtr->println(pwdArr);

		result = RedFly.join(ssidArr, pwdArr, INFRASTRUCTURE);

		if (result)
		{
			_debugSerialPtr->println("REDFLY JOIN ERR");
			for (;;)
				;
		}
		else
		{
			_debugSerialPtr->println("REDFLY BEGIN");
			result = RedFly.begin(1);
			if (result)
			{
				_debugSerialPtr->println("REDFLY BEGIN ERROR");
				RedFly.disconnect();
				for (;;)
					;
			}
			else
			{
				//RedFly.getlocalip(ip); //receive shield IP in case of DHCP/Auto-IP
				_debugSerialPtr->println("REDFLY SOCKETLISTEN");
				_http = RedFly.socketListen(PROTO_TCP, 80); //start listening on port 80
				if (_http == 0xFF)
				{
					_debugSerialPtr->println("REDFLY SOCKETLISTEN ERROR");
					RedFly.disconnect();
					for (;;)
						; //do nothing forevermore
				}
				else
				{
					_debugSerialPtr->println("REDFLY SOCKETLISTEN LISTENING");
					_listening = true;
				}
			}
		}
	}

}

void SAAPRedFly::receive()
{
	if (_listening)
	{
		uint8_t sock;
		char buf[512], *ptr;
		uint16_t buf_len, rd, len;

		//get data
		sock = 0xFF; //0xFF = return data from all open sockets
		ptr = buf;
		buf_len = 0;
		do
		{
			rd = RedFly.socketRead(&sock, &len, (uint8_t*) ptr, sizeof(buf) - buf_len);
			if ((rd != 0) && (rd != 0xFFFF)) //0xFFFF = connection closed
			{

				ptr += rd;
				buf_len += rd;
				_debugSerialPtr->print(buf[buf_len]);
				_debugSerialPtr->println("inWhile");
			}
		}
		while ((len != 0) && (buf_len < sizeof(buf)));

		//_debugSerialPtr->println("afterWhile");

		for (int i = 0; i < buf_len; i++)
		{
			char byte = buf[i];
			SAAP::onByteReceived(byte);
		}

		/*

		 if (buf_len > 0) _debugSerialPtr->print("received: ");


		 String msg = "";

		 for (int i = 0; i < buf_len; i++)
		 {
		 char byte = buf[i];
		 _debugSerialPtr->print(buf[i]);
		 msg += byte;
		 if (byte == ';')
		 {
		 //do sth
		 _debugSerialPtr->print("ne message:");
		 _debugSerialPtr->println(msg);
		 }
		 }

		 if (strncmp_P(buf, PSTR("anus"), 4) == 0)
		 {
		 RedFly.socketSendPGM(sock, PSTR("a1,2,3;"));
		 }
		 */

	}
}
