#include "Vector2.h"

#include "Core/CMath.h"

namespace LibMath
{
	Vector2& Vector2::operator/=(const Vector2& other)
	{
		// TODO Optimize to only have check in debug
		if (other.x == 0.0f || other.y == 0.f)
		{
			x = 0.0f;
			y = 0.0f;
			return *this;
		}


		x /= other.x;
		y /= other.y;
		return *this;
	}

	float Vector2::Magnitude() const
	{
		return sqrt(x * x + y * y);
	}
	
	Radian Vector2::ExtractAngleBetween(Vector2 lhs, Vector2 rhs)
	{
		float lhsSqMagnitude = lhs.SquareMagnitude();
		if (lhsSqMagnitude != 1.f)
		{
			lhs /= sqrt(lhsSqMagnitude);
		}

		float rhsSqMagnitude = rhs.SquareMagnitude();
		if (rhsSqMagnitude != 1.f)
		{
			rhs /= sqrt(rhsSqMagnitude);
		}

		return acos(lhs.Dot(rhs));
	}
}