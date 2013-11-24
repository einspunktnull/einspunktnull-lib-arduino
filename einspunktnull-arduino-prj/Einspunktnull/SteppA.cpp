/*
 *  SteppA.cpp - Library for use with Steppers-Hardware.
 *  Created by Albrecht Nitsche, October 29, 2010.
 *  Released into the public domain.
 */

#include "Arduino.h"
#include "SteppA.h"


/**********************************************/
/*                                            */
/*                   PUBLIC                   */
/*                                            */
/**********************************************/


SteppA::SteppA(int stepsPerRevolution, int type, int stepDelay, int pin1, int pin2, int pin3, int pin4)
{
	_stepsPerRevolution = stepsPerRevolution;
	
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);

	_stepDelay = stepDelay;
	_pin1 = pin1;
	_pin2 = pin2;
	_pin3 = pin3;
	_pin4 = pin4;

	_count = 0;
	_dir = 1;
	_type = type;

}

int SteppA::TYPE_A = 0;
int SteppA::TYPE_B = 1;

void SteppA::step(int steps)
{
	if (steps > 0) _dir = 1;
	else _dir = -1;
	for (int i = 0; i < abs(steps); i++)
	{
		doStep();
		_count += _dir;
		if (_count < 0) _count = 3;
		if (_count > 3) _count = 0;
	}
}

void SteppA::setStepDelay(int delay)
{
	_stepDelay = delay;
}

void SteppA::setStepsPerRevolution(int spr)
{
	_stepsPerRevolution = spr;
}

void SteppA::setPins(int pin1, int pin2, int pin3, int pin4)
{
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);
	
	_pin1 = pin1;
	_pin2 = pin2;
	_pin3 = pin3;
	_pin4 = pin4;
}

void SteppA::setRPM(int rpm)
{
	_stepDelay = 60000/(rpm*_stepsPerRevolution);
}

/**********************************************/
/*                                            */
/*                  PRIVATE                   */
/*                                            */
/**********************************************/


int SteppA::sequenceA[4][4] = {{	0,0,0,1},{	0,0,1,0},{	0,1,0,0},{	1,0,0,0}};
int SteppA::sequenceB[4][4] = {{	1,0,1,0},{	0,1,1,0},{	0,1,0,1},{	1,0,0,1}};

void SteppA::doStep()
{
	if(_type==TYPE_A)
	{
		digitalWrite(_pin1, sequenceA[_count][0]);
		digitalWrite(_pin2, sequenceA[_count][1]);
		digitalWrite(_pin3, sequenceA[_count][2]);
		digitalWrite(_pin4, sequenceA[_count][3]);
	}
	else if(_type==TYPE_B)
	{
		digitalWrite(_pin1, sequenceB[_count][0]);
		digitalWrite(_pin2, sequenceB[_count][1]);
		digitalWrite(_pin3, sequenceB[_count][2]);
		digitalWrite(_pin4, sequenceB[_count][3]);
	}
	delay( _stepDelay);
}

