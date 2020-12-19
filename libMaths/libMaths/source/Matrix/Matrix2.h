#pragma once

#include <cstring>

namespace LibMath
{
	struct Vector2;

	struct Matrix2
	{
		Matrix2() { Clear(); }
		Matrix2(Matrix2 const& other) = default;
		Matrix2& operator=(const Matrix2& other) = default;
		Matrix2(float diagonalValue);
		Matrix2(float real, float imaginary); // complex number
		Matrix2(float a, float b, float c, float d);
		~Matrix2() = default;

		static Matrix2 Identity() { return Matrix2(1.f); }

		Matrix2& operator*=(Matrix2 const& other) { *this = *this * other; }
		friend Matrix2 operator*(Matrix2 const& lhs, Matrix2 const& rhs);
		friend Vector2 operator*(Vector2 const& lhs, Matrix2 const& rhs);

		void Clear() { std::memset(&raw, 0, sizeof(raw)); }

		float const* Data() const { return raw; }

		float raw[4];
	};
}