#ifndef LinkspriteJPEGColorCamera_h
#define LinkspriteJPEGColorCamera_h


#include <avr/pgmspace.h>
#include "Arduino.h"
#include "SoftwareSerial.h"

class LinkspriteJPEGColorCamera
{
	public:
		LinkspriteJPEGColorCamera(SoftwareSerial *_cameraPort);
		void begin(void);
		int reset(char * response);
		int getSize(char * response, int * size);
		int takePicture(char * response);
		int stopPictures(char * response);
		int readData(char * response, int address);

	private:
		SoftwareSerial *_cameraPort;
		int sendCommand(const char * command, char * response, int length);
};

#endif
