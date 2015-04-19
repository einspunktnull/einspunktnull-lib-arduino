#include "KbdRptParser.h"

USB Usb;

HIDBoot<HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);

void KbdRptParser::init()
{
	//while (!Serial);
	//Serial.println("KEYBOARD START");
	if (Usb.Init() == -1)
	{
		//Serial.println("OSC did not start.");
	}
	delay(500);

	KbdRptParser *prs = this;

	HidKeyboard.SetReportParser(0, (HIDReportParser*) prs);

	//Serial.println("KEYBOARD READY");
}

void KbdRptParser::task()
{
	Usb.Task();
}

void KbdRptParser::onKeyUp(FunctionPointer fctPtr)
{
	_onKeyUpPtr = fctPtr;
}

void KbdRptParser::onKeyDown(FunctionPointer fctPtr)
{
	_onKeyDownPtr = fctPtr;
}

void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
	MODIFIERKEYS mod;
	*((uint8_t*) &mod) = m;
	//Serial.print((mod.bmLeftCtrl == 1) ? "C" : " ");
	//Serial.print((mod.bmLeftShift == 1) ? "S" : " ");
	//Serial.print((mod.bmLeftAlt == 1) ? "A" : " ");
	//Serial.print((mod.bmLeftGUI == 1) ? "G" : " ");

	//Serial.print(" >");
	//PrintHex<uint8_t>(key, 0x80);
	//Serial.print("< ");

	//Serial.print((mod.bmRightCtrl == 1) ? "C" : " ");
	//Serial.print((mod.bmRightShift == 1) ? "S" : " ");
	//Serial.print((mod.bmRightAlt == 1) ? "A" : " ");
	//Serial.println((mod.bmRightGUI == 1) ? "G" : " ");
}
;

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after)
{

	MODIFIERKEYS beforeMod;
	*((uint8_t*) &beforeMod) = before;

	MODIFIERKEYS afterMod;
	*((uint8_t*) &afterMod) = after;

	/*
	if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl)
	{
		Serial.println("LeftCtrl changed");
	}
	if (beforeMod.bmLeftShift != afterMod.bmLeftShift)
	{
		Serial.println("LeftShift changed");
	}
	if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt)
	{
		Serial.println("LeftAlt changed");
	}
	if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI)
	{
		Serial.println("LeftGUI changed");
	}

	if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl)
	{
		Serial.println("RightCtrl changed");
	}
	if (beforeMod.bmRightShift != afterMod.bmRightShift)
	{
		Serial.println("RightShift changed");
	}
	if (beforeMod.bmRightAlt != afterMod.bmRightAlt)
	{
		Serial.println("RightAlt changed");
	}
	if (beforeMod.bmRightGUI != afterMod.bmRightGUI)
	{
		Serial.println("RightGUI changed");
	}
	*/

}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
	//Serial.print("cUP ");
	//PrintKey(mod, key);
	//uint8_t c = OemToAscii(mod, key);
	//if (c) OnKeyPressed(c);

	void (*FunctionPointer)(uint8_t mod, uint8_t key) = _onKeyUpPtr;
	FunctionPointer(mod, key);
}

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
	//Serial.print("cDN ");
	//PrintKey(mod, key);
	//uint8_t c = OemToAscii(mod, key);
	//if (c) OnKeyPressed(c);

	void (*FunctionPointer)(uint8_t mod, uint8_t key) = _onKeyDownPtr;
	FunctionPointer(mod, key);
}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
	//Serial.print("cASCII: ");
	//Serial.println((char) key);
}
;
