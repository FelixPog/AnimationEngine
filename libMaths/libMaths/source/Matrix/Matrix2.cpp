#include "Matrix2.h"
#include "Vector/Vector.h"

namespace LibMath
{
	Matrix2::Matrix2(float diagonalValue)
	{
		raw[0] = diagonalValue;
		raw[1] = 0.f;
		raw[2] = 0.f;
		raw[3] = diagonalValue;
	}

	Matrix2::Matrix2(float real, float imaginary)
	{
		raw[0] = real;
		raw[1] = -imaginary;
		raw[2] = imaginary;
		raw[3] = real;
	}

	Matrix2::Matrix2(float a, float b, float c, float d)
	{
		raw[0] = a;
		raw[1] = b;
		raw[2] = c;
		raw[3] = d;
	}

	Matrix2 operator*(Matrix2 const& lhs, Matrix2 const& rhs)
	{
		Matrix2 result;

		result.raw[0] = lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[2];
		result.raw[1] = lhs.raw[0] * rhs.raw[1] + lhs.raw[1] * rhs.raw[3];
		result.raw[2] = lhs.raw[2] * rhs.raw[0] + lhs.raw[3] * rhs.raw[2];
		result.raw[3] = lhs.raw[2] * rhs.raw[1] + lhs.raw[3] * rhs.raw[3];

		return result;
	}

	Vector2 operator*(Vector2 const& lhs, Matrix2 const& rhs)
	{
		Vector2 result;

		//result.raw[0] = lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[2];
		//result.raw[1] = lhs.raw[0] * rhs.raw[1] + lhs.raw[1] * rhs.raw[3];
		result.x = lhs.x * rhs.raw[0] + lhs.y * rhs.raw[2];
		result.y = lhs.x * rhs.raw[1] + lhs.y * rhs.raw[3];

		return result;
	}
}