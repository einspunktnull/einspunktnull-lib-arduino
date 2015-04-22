#include "Arduino.h"
#include "PololuMD03A.h"

PololuMD03A::PololuMD03A()
{
	_pin1PWM = 0;
	_pin1A = 0;
	_pin1B = 0;
	_pin2PWM = 0;
	_pin2A = 0;
	_pin2B = 0;
}

void PololuMD03A::initialize(const int pinPWM1, const int pinA1, const int pinB1, const int pinPWM2, const int pinA2, const int pinB2)
{
	_pin1PWM = pinPWM1;
	_pin1A = pinA1;
	_pin1B = pinB1;
	_pin2PWM = pinPWM2;
	_pin2A = pinA2;
	_pin2B = pinB2;

	pinMode(_pin1PWM, OUTPUT);
	pinMode(_pin1A, OUTPUT);
	pinMode(_pin1B, OUTPUT);
	pinMode(_pin2PWM, OUTPUT);
	pinMode(_pin2A, OUTPUT);
	pinMode(_pin2B, OUTPUT);
}

void PololuMD03A::stop()
{
	setSpeeds(0, 0);
}
void PololuMD03A::setSpeeds(const int speed1, const int speed2)
{
	setSpeed1(speed1);
	setSpeed2(speed2);
}

void PololuMD03A::setSpeed1(const int speed1)
{
	_setSpeed(_pin1PWM, _pin1A, _pin1B, speed1);
}

void PololuMD03A::setSpeed2(const int speed2)
{
	_setSpeed(_pin2PWM, _pin2A, _pin2B, speed2);
}

void PololuMD03A::_setSpeed(const int pwm, const int a, const int b, const int speed)
{
	if (speed == 0)
	{
		analogWrite(pwm, 0);
		digitalWrite(a, LOW);
		digitalWrite(b, LOW);
	}
	
	int speedVal = map(speed, -100, 100, -255, 255);
	
	analogWrite(pwm, abs(speedVal));
	digitalWrite(a, speedVal >= 0 ? HIGH : LOW);
	digitalWrite(b, speedVal >= 0 ? LOW : HIGH);
}

