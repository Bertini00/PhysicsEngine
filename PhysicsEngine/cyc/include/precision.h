#pragma once
#include <float.h>

/** Define the precision of the square root operator */


namespace cyclone
{


	/**
	* Defines a real number precision. Cyclone can be compiled in
	* single- or double-precision versions. By default single precision
	* is provided
	*/
	typedef float real;

#define real_sqrt sqrtf
#define REAL_MAX FLT_MAX
#define real_pow powf
	// Defines the precision of the absolute magnitude operator
#define real_abs fabsf
}