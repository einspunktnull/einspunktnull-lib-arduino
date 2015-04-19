#ifndef KBDRPTPARSER_H_
#define KBDRPTPARSER_H_

#include <hidboot.h>
#include <usbhub.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

class KbdRptParser: public KeyboardReportParser
{
		void PrintKey(uint8_t mod, uint8_t key);

	private:
		typedef void (*FunctionPointer)(uint8_t mod, uint8_t key);
		FunctionPointer _onKeyUpPtr;
		FunctionPointer _onKeyDownPtr;

	public:
		void init();
		void task();
		void onKeyUp(FunctionPointer fctPtr);
		void onKeyDown(FunctionPointer fctPtr);

	protected:
		virtual void OnControlKeysChanged(uint8_t before, uint8_t after);

		virtual void OnKeyDown(uint8_t mod, uint8_t key);
		virtual void OnKeyUp(uint8_t mod, uint8_t key);
		virtual void OnKeyPressed(uint8_t key);
};

#endif
