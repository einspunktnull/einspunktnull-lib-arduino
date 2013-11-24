#include "Arduino.h"

#ifndef UTILS_H_
#define UTILS_H_



class Utils
{
	public:
		static bool intEqualsInt(int v1, int v2, int tol);
		static void stringSplit(String src, char delimiter, String stringArray[]);
		static int stringAsInt(String src);
		static long stringAsLong(String src);
};

#endif
