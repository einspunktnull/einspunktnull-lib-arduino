/*
 WStringExt.h - Library for extended Usage of String-Object.
 Created by Albrecht Nitsche, October 20, 2010.
 Released into the public domain.
 */

#ifndef WStringExt_h
#define WStringExt_h

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

class StringExt: public String
{
	public:
		//constructors
		StringExt(const char *value = "");
		StringExt(const String &value);
		StringExt(const char);
		StringExt(const unsigned char);
		StringExt(const int, const int base = 10);
		StringExt(const unsigned int, const int base = 10);
		StringExt(const long, const int base = 10);
		StringExt(const unsigned long, const int base = 10);
		// ~String() { free(_buffer); _length = _capacity = 0;}

		// general methods
		char *asCharArray();
		double asInt();
		double asDouble();
		void split(char, String[]);
		bool contains(String);

	protected:

	private:

};

#endif
