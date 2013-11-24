/*
 WStringExt.cpp - Library for extended Usage of String-Object.
 Created by Albrecht Nitsche, October 20, 2010.
 Released into the public domain.
 */

#include "Arduino.h"
#include "WStringExt.h"

//constructors
StringExt::StringExt(const char *value) :
	String(value)
{
}
StringExt::StringExt(const String &value) :
	String(value)
{
}
StringExt::StringExt(const char value) :
	String(value)
{
}
StringExt::StringExt(const unsigned char value) :
	String(value)
{
}
StringExt::StringExt(const int value, const int base) :
	String(value, base)
{
}
StringExt::StringExt(const unsigned int value, const int base) :
	String(value, base)
{
}
StringExt::StringExt(const long value, const int base) :
	String(value, base)
{
}
StringExt::StringExt(const unsigned long value, const int base) :
	String(value, base)
{
}


// general methods

char* StringExt::asCharArray()
{
	char* resp = (char*) malloc(sizeof(char) * (len + 1));
	if (!resp) return NULL;
	return (char*) memcpy(resp, buffer, len + 1);
}

double StringExt::asInt()
{
	return atoi(asCharArray());
}

double StringExt::asDouble()
{
	return atof(asCharArray());
}

void StringExt::split(char delimiter, String stringArray[])
{
	int from = 0;
	int count = 0;

	for (int i = 0; i < length(); i++)
	{
		if (char(charAt(i)) == delimiter)
		{
			stringArray[count] = substring(from, i);
			from = i + 1;
			count++;
		}
		else if (i == length() - 1)
		{
			stringArray[count] = substring(from, i + 1);
			count++;
		}
	}
}

bool StringExt::contains(String str)
{
	for (int i = 0; i < length(); i++)
	{
		if (substring(i, i + str.length()).equals(str)) return true;
	}
	return false;
}
