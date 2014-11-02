#include "triggmath.h"

#pragma region SquareRoot

float Math::fastSqrtf(float x)
{
	float xhalf = 0.5f*x;
	__int32 i = *(__int32*)&x;	// get bits for floating value
	i = 0x5f375a86 - (i >> 1);	// gives initial guess y0
	float j = *(float*)&i;		// convert bits back to float
	j = j*(1.5f - xhalf*j*j);	// Newton step, repeating increases accuracy
	return x*j;
}

#pragma endregion

float Math::Clamp(float value, float min, float max)
{
	return value > max ? max : value < min ? min : value;
}
double Math::Clamp(double value, double min, double max)
{
	return value > max ? max : value < min ? min : value;
}
