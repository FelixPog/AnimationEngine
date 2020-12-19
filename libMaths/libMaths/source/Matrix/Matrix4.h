#pragma once

#include <cstring>

#include "Core/Angle.h"
#include "Vector/Vector.h"
#include "Quaternion/Quaternion.h"

namespace LibMath
{
	struct Vector3;

	struct const_col
	{
		const_col(float const* ptr) : m_ptr(ptr) {}
		float const* m_ptr;

		float operator[](int idx) const { return m_ptr[idx * 4]; }
	};

	struct col
	{
		col(float* ptr) : m_ptr(ptr) {}
		float* m_ptr;

		float& operator[](int idx) { return m_ptr[idx * 4]; }
	};

	struct row
	{
		row(float* ptr) : m_ptr(ptr) {}
		float* m_ptr;

		float& operator[](int idx) { return m_ptr[idx]; }
		row& operator=(const_col const& other) { for (int i = 0; i < 4; i++) (*this)[i] = other[i]; return *this; }
	};

	struct const_row
	{
		const_row(float const* ptr) : m_ptr(ptr) {}
		float const* m_ptr;

		float operator[](int idx) const { return m_ptr[idx]; }
	};

	struct GridRow
	{
		float values[4];
	};

	struct GridView
	{
		GridRow rows[4];
	};

	struct Matrix4
	{
		Matrix4() { Clear(); /*gridview = new(raw)GridView;*/ }
		Matrix4(Matrix4 const& other) = default;
		Matrix4& operator=(const Matrix4& other) = default;
		Matrix4(float diagonalValue);
		~Matrix4() = default;

		static Matrix4 Identity() { return Matrix4(1.f); }
		static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static Matrix4 Perspective(Radian fieldOfView, float aspectRatio, float near, float far);
		static Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
		static Matrix4 Rotation(Quaternion quaternion);
		static Matrix4 Rotation(Radian x, Radian y, Radian z);
		static Matrix4 Rotation(const Vector3& vec, bool radian);
		static Matrix4 Scaling(float x, float y, float z);
		static Matrix4 Scaling(const Vector3& vec);
		static Matrix4 Translation(float x, float y, float z);
		static Matrix4 Translation(const Vector3& vec);

		//Maybe swap order of multiplication
		Matrix4& Rotate(Quaternion const& quaternion) { *this = Rotation(quaternion) * (*this); return *this; }
		Matrix4& Rotate(Radian x, Radian y, Radian z) { *this = Rotation(x, y, z) * (*this); return *this; }
		Matrix4& Rotate(const Vector3& vec, bool radian) { *this = Rotation(vec, radian)* (*this); return *this; }

		Matrix4& Scale(float x, float y, float z) { *this = Scaling(x, y, z)* (*this); return *this; }
		Matrix4& Scale(const Vector3& vec) { *this = Scaling(vec)* (*this); return *this; }

		Matrix4& Translate(float x, float y, float z) { *this = Translation(x, y, z)* (*this); return *this; }
		Matrix4& Translate(const Vector3& vec) { *this = Translation(vec)* (*this); return *this; }

		bool operator==(const Matrix4& other) const;
		bool operator!=(const Matrix4& other) const { return !(*this == other); }

		row operator[](int idx) { return row(&raw[idx * 4]); }
		const_row operator[](int idx) const { return const_row(&raw[idx * 4]); }

		LibMath::col col(int idx) { return LibMath::col(&raw[idx]); }
		const_col col(int idx) const { return const_col(&raw[idx]); }

		Matrix4 operator*(Matrix4 const& other) const;
		Matrix4& operator*=(Matrix4 const& other);

		Vector4 operator*(Vector4 const& other) const;

		friend Vector4 operator*(Vector4 const& otherVec, Matrix4 const& thisMat);

		float Determinant() const;

		[[nodiscard]] Vector4 GetTranslation() const { return Vector4((*this)[3][0], (*this)[3][1], (*this)[3][2], (*this)[3][3]); }
		static Vector4 GetTranslation(Matrix4& Matrix4) { return Matrix4.GetTranslation(); }

		void Transpose() { *this = GetTranspose(); }
		[[nodiscard]] Matrix4 GetTranspose() const;
		static void Transpose(Matrix4& Matrix4) { Matrix4.Transpose(); }

		void Inverse() { *this = GetInverse(); }
		[[nodiscard]] Matrix4 GetInverse() const;
		static void Inverse(Matrix4& Matrix4) { Matrix4.Inverse(); }

		void Adjoint() { *this = GetAdjoint(); }
		[[nodiscard]] Matrix4 GetAdjoint() const;
		static void Adjoint(Matrix4& Matrix4) { Matrix4.Adjoint(); }

		Matrix4 NormalMatrix4() const;
		static void NormalMatrix4(Matrix4 const& Matrix4);

		void Clear() { std::memset(&raw, 0, sizeof(raw)); }

		float const* Data() const { return raw; }

		float raw[16];
		//GridView* gridview;

	private:

		float Determinant(int ignoredRow, int ignoredCol) const;
	};
}
