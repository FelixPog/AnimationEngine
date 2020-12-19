#include "Interpolation.h"

#include "Core/CMath.h"
#include "Vector/Vector3.h"
#include "Quaternion/Quaternion.h"

namespace LibMath::Interpolation
{
	Vector3 Slerp(const Vector3& start, const Vector3& end, const float delta)
	{
		const float dot = start.Dot(start);
		const float clamped = Clamp(dot, -1.0f, 1.0f);

		// Angle between both vectors that corresponds to delta
		const Radian theta = acos(clamped) * delta;

		// Vector that corresponds to delta
		Vector3 relativeVec = end - start * clamped;
		relativeVec.Normalize();

		return ((start * cos(theta)) + (relativeVec * sin(theta)));
	}

	Quaternion Slerp(const Quaternion& start, const Quaternion& end, const float delta)
	{
		Quaternion nEnd = end;

		// Compute the cosine of the angle between the two vectors.
		float cosTheta = start.DotProduct(end);

		// If cosTheta < 0, the interpolation will take the long way around the sphere.
		// To fix this, one quat must be negated.
		if (cosTheta < 0.0f)
		{
			nEnd.Negate();
			cosTheta = -cosTheta;
		}

		const float DOT_THRESHOLD = 0.9995f;
		if (cosTheta > DOT_THRESHOLD)
		{
			// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
			return Lerp(start, nEnd, delta);
		}

		Radian angle = acos(cosTheta);

		return (start * sin((1 - delta) * angle) + nEnd * sin(delta * angle)) * (1 / sin(angle));
	}

	Vector3 Nlerp(const Vector3& start, const Vector3& end, const float delta)
	{
		return Lerp(start, end, delta).Normalize();
	}

	Quaternion Nlerp(const Quaternion& start, const Quaternion& end, const float delta)
	{
		return Lerp(start, end, delta).GetNormalize();
	}

	float SmoothStep(const float start, const float end, const float delta)
	{
		const float clampedDelta = Clamp((delta - start) / (end - start), 0.f, 1.f);

		return clampedDelta * clampedDelta * (3 - 2 * clampedDelta);
	}

	float SmootherStep(const float start, const float end, const float delta)
	{
		const float clampedDelta = Clamp((delta - start) / (end - start), 0.f, 1.f);

		return clampedDelta * clampedDelta * clampedDelta * (clampedDelta * (clampedDelta * 6 - 15) + 10);
	}

	float MapInRange(const float value, const float inMin, const float inMax, const float outMin, const float outMax)
	{
		return (value - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
	}

	float EaseIn(const float delta, const EaseFunctions easeFunction)
	{
		float x = Clamp(delta, 0.f, 1.f);

		const float c1 = 1.70158f;
		const float c3 = c1 + 1.f;
		const float c4 = (2.f * PI) / 3.f;

		switch (easeFunction)
		{
		case EaseFunctions::EASE_SINE:
			return 1.f - cos(Radian(x * PI) / 2.f);

		case EaseFunctions::EASE_QUAD:
			return Powf(x, 2.f);

		case EaseFunctions::EASE_CUBIC:
			return Powf(x, 3.f);

		case EaseFunctions::EASE_QUART:
			return Powf(x, 4.f);

		case EaseFunctions::EASE_QUINT:
			return Powf(x, 5.f);

		case EaseFunctions::EASE_EXPO:
			if (x == 0.f)
				return 0.f;

			return Powf(2, 10.f * x - 10.f);

		case EaseFunctions::EASE_CIRC:
			return 1 - sqrt(1.f - Powf(x, 2));

		case EaseFunctions::EASE_BACK:
			return c3 * Powf(x, 3.f) - c1 * Powf(x, 2.f);

		case EaseFunctions::EASE_ELASTIC:
			if (x == 0.f)
				return 0.f;
			if (x == 1.f)
				return 1.f;

			return -1.f * Powf(2.f, 10.f * x - 10.f) * sin(Radian((x * 10.f - 10.75f) * c4));

		case EaseFunctions::EASE_BOUNCE:
			return 1.f - EaseOut(1.f - x, EaseFunctions::EASE_BOUNCE);
		}
		return 0.f;
	}

	float EaseOut(const float delta, const EaseFunctions easeFunction)
	{
		float x = Clamp(delta, 0.f, 1.f);

		const float c1 = 1.70158f;
		const float c3 = c1 + 1;
		const float c4 = (2.f * PI) / 3.f;
		const float n1 = 7.5625f;
		const float d1 = 2.75f;

		switch (easeFunction)
		{
		case EaseFunctions::EASE_SINE:
			return sin(Radian(x * PI) / 2.f);

		case EaseFunctions::EASE_QUAD:
			return 1.f - (1.f - x) * (1.f - x);

		case EaseFunctions::EASE_CUBIC:
			return 1 - Powf(1.f - x, 3.f);

		case EaseFunctions::EASE_QUART:
			return 1 - Powf(1.f - x, 4.f);

		case EaseFunctions::EASE_QUINT:
			return 1 - Powf(1.f - x, 5.f);

		case EaseFunctions::EASE_EXPO:
			if (x == 1.f)
				return 1.f;

			return 1.f - Powf(2.f, -10.f * x);

		case EaseFunctions::EASE_CIRC:
			return sqrt(1.f - Powf(x - 1.f, 2.f));

		case EaseFunctions::EASE_BACK:
			return 1.f + c3 * Powf(x - 1.f, 3.f) + c1 * Powf(x - 1.f, 2.f);

		case EaseFunctions::EASE_ELASTIC:
			if (x == 0.f)
				return 0.f;
			if (x == 1.f)
				return 1.f;

			return Powf(2.f, -10.f * x) * sin(Radian(x * 10.f - 0.75f) * c4) + 1.f;

		case EaseFunctions::EASE_BOUNCE:
			if (x < 1.f / d1)
				return n1 * x * x;
			if (x < 2.f / d1)
				return n1 * (x -= 1.5f / d1) * x + 0.75f;
			if (x < 2.5f / d1)
				return n1 * (x -= 2.25f / d1) * x + 0.9375f;

			return n1 * (x -= 2.625f / d1) * x + 0.984375f;
		}
		return 0.f;
	}

	float EaseInOut(const float delta, const EaseFunctions easeFunction)
	{
		float x = Clamp(delta, 0.f, 1.f);

		const float c1 = 1.70158f;
		const float c2 = c1 * 1.525f;
		const float c5 = (2.f * PI) / 4.5f;

		switch (easeFunction)
		{
		case EaseFunctions::EASE_SINE:
			return -1.f * ((cos(Radian(PI * x)) - 1.f) / 2.f);

		case EaseFunctions::EASE_QUAD:
			if (x < 0.5f)
				return 2.f * Powf(x, 2.f);
			return 1.f - Powf(-2.f * x + 2.f, 2.f) / 2.f;

		case EaseFunctions::EASE_CUBIC:
			if (x < 0.5f)
				return 4.f * Powf(x, 3.f);
			return 1.f - Powf(-2.f * x + 2.f, 3.f) / 2.f;

		case EaseFunctions::EASE_QUART:
			if (x < 0.5f)
				return 8.f * Powf(x, 4.f);
			return 1.f - Powf(-2.f * x + 2.f, 4.f) / 2.f;

		case EaseFunctions::EASE_QUINT:
			if (x < 0.5f)
				return 16.f * Powf(x, 5.f);
			return 1.f - Powf(-2.f * x + 2.f, 5.f) / 2.f;

		case EaseFunctions::EASE_EXPO:
			if (x == 0.f)
				return 0.f;
			if (x == 1.f)
				return 1.f;
			if (x < 0.5f)
				return Powf(2.f, 20.f * x - 10.f) / 2.f;
			return (2.f - Powf(2.f, -20.f * x + 10.f)) / 2.f;

		case EaseFunctions::EASE_CIRC:
			if (x < 0.5f)
				return (1.f - sqrt(1.f - Powf(2.f * x, 2.f))) / 2.f;
			return (sqrt(1 - Powf(-2.f * x + 2.f, 2.f)) + 1.f) / 2.f;

		case EaseFunctions::EASE_BACK:
			if (x < 0.5f)
				return (Powf(2.f * x, 2.f) * ((c2 + 1.f) * 2.f * x - c2)) / 2.f;
			return (Powf(2.f * x - 2.f, 2.f) * ((c2 + 1.f) * (x * 2.f - 2.f) + c2) + 2.f) / 2.f;

		case EaseFunctions::EASE_ELASTIC:
			if (x == 0.f)
				return 0.f;
			if (x == 1.f)
				return 1.f;
			if (x < 0.5f)
				return -(Powf(2.f, 20.f * x - 10.f) * sin(Radian(20.f * x - 11.125f) * c5)) / 2.f;
			return (Powf(2.f, -20.f * x + 10.f) * sin(Radian(20.f * x - 11.125f) * c5)) / 2.f + 1.f;

		case EaseFunctions::EASE_BOUNCE:
			if (x < 0.5f)
				return (1 - EaseOut(1.f - 2.f * x, EaseFunctions::EASE_BOUNCE)) / 2.f;
			return (1 + EaseOut(2.f * x - 1.f, EaseFunctions::EASE_BOUNCE)) / 2.f;
		}

		return 0.f;
	}
}