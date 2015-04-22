// ensure this library description is only included once
#ifndef PololuMD03A_h
#define PololuMD03A_h

class PololuMD03A
{
	private:
		int _pin1PWM;
		int _pin1A;
		int _pin1B;
		int _pin2PWM;
		int _pin2A;
		int _pin2B;

		void _setSpeed(const int pwm, const int a, const int b, const int speed);
	public:
		PololuMD03A();

		void initialize(const int pinPWM1, const int pinA1, const int pinB1, const int pinPWM2, const int pinA2, const int pinB2);
		void setSpeeds(const int speed1, const int speed2);
		void setSpeed1(const int speed1);
		void setSpeed2(const int speed2);
		void stop();

};

#endif

