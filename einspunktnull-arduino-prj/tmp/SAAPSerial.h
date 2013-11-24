#ifndef SAAPSERIAL_H_
#define SAAPSERIAL_H_





class SAAPSerial:public SAAP
{

	private:


		unsigned long _timeout;



	public:
		SAAPSerial();
		void initialize(ErrorFunctionPointer errorFctPtr, HardwareSerial *serialPtr, long baudrate, unsigned long timeout);
		void receive();

};

#endif

