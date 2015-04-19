#include <Arduino.h>
#include "Mausi.h"

Mausi::Mausi()
{
}

void Mausi::begin()
{
	Mouse.begin();
}

void Mausi::move(int diffX, int diffY, int diffWheel)
{
	while (abs(diffX) > 0 || abs(diffY) > 0)
	{
		Serial.print(diffX);

		int absDiffX = abs(diffX);

		int x = 0;
		int y = 0;
		int scroll = 0;

		if (absDiffX >= 100)
		{
			if (diffX > 0)
			{
				x = -100;
			}
			else if (diffX < 0)
			{
				x = 100;
			}
			diffX += x;
		}
		else if (absDiffX > 0)
		{
			x = -diffX;
			diffX += x;
		}

		Serial.print(" ");
		Serial.println(x);

		Mouse.move(-x, 0, 0);

	}
}

