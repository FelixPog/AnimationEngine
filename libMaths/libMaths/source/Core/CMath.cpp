#include "CMath.h"

#include <cmath>
#include <algorithm>

namespace LibMath
{
	float ceil(float value)
	{
		return std::ceilf(value);
	}

	float floor(float value)
	{
		return std::floorf(value);
	}

	float fmod(float value, float modulo)
	{
		return std::fmod(value, modulo);
	}

	float ldexpf(float value, int baseShift)
	{
		return std::ldexpf(value, baseShift);
	}

	float sqrt(float value)
	{
		return std::sqrtf(value);
	}
}

float LibMath::Clamp(const float target, const float min, const float max)
{
	return std::clamp(target, min, max);
}


float LibMath::Powf(const float x, const float y)
{
	return powf(x, y);
}
