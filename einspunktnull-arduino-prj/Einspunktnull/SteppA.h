/*
 *  SteppA.h - Library for use with Steppers-Hardware.
 *  Created by Albrecht Nitsche, October 29, 2010.
 *  Released into the public domain.
 */

#ifndef SteppA_h
#define SteppA_h

#include "Arduino.h"

class SteppA
{
	public:
		SteppA(int, int, int, int, int, int, int);
		//unipolar
		static int TYPE_A;
		//bipolar
		static int TYPE_B;
		void step(int);
		void setStepDelay(int);
		void setStepsPerRevolution(int);
		void setPins(int, int, int, int);
		void setRPM(int);
	private:
		int _type;
		int _stepDelay;
		int _stepsPerRevolution;
		int _pin1;
		int _pin2;
		int _pin3;
		int _pin4;
		
		int _count;
		int _dir;

		static int sequenceA[4][4];
		static int sequenceB[4][4];
		
		void doStep();
};

#endif
