#include <math.h>
#include "ASCIIConverter.h"


char ASCIIConverter::norm2ASCII(float fVal)
{
	fVal = (fVal < 0.f) ? 0.f : (fVal > 1.f) ? 1.f : fVal;

	fVal = powf(fVal, 2.f);

	const int INDEX = roundf(fVal * (ASCII_TABLE_SIZE - 1));

	return ASCII_TABLE[INDEX];
}
