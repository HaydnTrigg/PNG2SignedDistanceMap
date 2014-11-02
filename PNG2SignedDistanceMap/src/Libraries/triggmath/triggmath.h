#ifndef _TRIGGMATH_H
#define _TRIGGMATH_H

#define Min(a,b) (((a) < (b)) ? (a) : (b))
#define Min3(a,b,c) (((a) < (c)) ? (((a) < (b)) ? (a) : (b)) : (c))
#define Max(a,b) (((a) > (b)) ? (a) : (b))
#define Max3(a,b,c) (((a) > (c)) ? (((a) > (b)) ? (a) : (b)) : (c))

namespace Math
{
	// :: Square Root ::
	//Calculates an approximate single precision Square Root
	extern float fastSqrtf(float x);

	extern float Clamp(float value, float min, float max);
	extern double Clamp(double value, double min, double max);
}

#endif