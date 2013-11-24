#include "Arduino.h"
#include "Utils.h"

bool Utils::intEqualsInt(int v1, int v2, int tol)
{
	//Serial.print("Test");
	int diff = abs(v1 - v2);
	return diff <= tol;
}

void Utils::stringSplit(String src, char delimiter, String stringArray[])
{
	int from = 0;
	int count = 0;

	for (int i = 0; i < src.length(); i++)
	{
		if (char(src.charAt(i)) == delimiter)
		{
			stringArray[count] = src.substring(from, i);
			from = i + 1;
			count++;
		}
		else if (i == src.length() - 1)
		{
			stringArray[count] = src.substring(from, i + 1);
			count++;
		}
	}
}


int Utils::stringAsInt(String src)
{
	int len = src.length() + 1;
	char srcArr[len];
	src.toCharArray(srcArr, len);
	return atoi(srcArr);
}

long Utils::stringAsLong(String src)
{
	int len = src.length() + 1;
	char srcArr[len];
	src.toCharArray(srcArr, len);
	return atol(srcArr);
}

