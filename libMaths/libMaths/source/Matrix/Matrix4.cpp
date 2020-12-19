#include "Matrix4.h"
#include "Vector/Vector.h"

namespace LibMath
{
	Matrix4::Matrix4(float diagonalValue)
	{
		Clear();
		/*gridview = new(raw)GridView;*/

		raw[0] = diagonalValue;
		raw[5] = diagonalValue;
		raw[10] = diagonalValue;
		raw[15] = diagonalValue;
	}


	Matrix4 Matrix4::Orthographic(float l, float r, float b, float t, float n, float f)
	{
		Matrix4 result;

		result.raw[0] = 2 / (r - l);
		result.raw[5] = 2 / (t - b);
		result.raw[10] = -2 / (f - n);

		result.raw[12] = -(r + l) / (r - l);
		result.raw[13] = -(t + b) / (t - b);
		result.raw[14] = -(f + n) / (f - n);
		result.raw[15] = 1.f;

		return result;
	}

	Matrix4 Matrix4::Perspective(Radian fov, float ar, float n, float f)
	{
		Matrix4 result;

		float t = tan(fov / 2.f) * n;
		float r = t * ar;

		result.raw[0] = n / r;
		result.raw[5] = n / t;
		result.raw[10] = -(f + n) / (f - n);
		result.raw[11] = -1.f;
		result.raw[14] = -(2.f * f * n) / (f - n);

		return result;
	}

	Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
	{
		Matrix4 result;

		Vector3 X, Y, Z;
		Z = eye - center;
		Z.Normalize();
		Y = up;
		X = Y.Cross(Z);
		Y = Z.Cross(X);
		X.Normalize();
		Y.Normalize();

		result.raw[0] = X.x;
		result.raw[4] = X.y;
		result.raw[8] = X.z;
		result.raw[12] = -X.Dot(eye);
		result.raw[1] = Y.x;
		result.raw[5] = Y.y;
		result.raw[9] = Y.z;
		result.raw[13] = -Y.Dot(eye);
		result.raw[2] = Z.x;
		result.raw[6] = Z.y;
		result.raw[10] = Z.z;
		result.raw[14] = -Z.Dot(eye);
		result.raw[3] = 0;
		result.raw[7] = 0;
		result.raw[11] = 0;
		result.raw[15] = 1.0f;

		return result;
	}

	Matrix4 Matrix4::Rotation(Quaternion quaternion)
	{
		Matrix4 result;

		float xx = quaternion.X * quaternion.X;
		float yy = quaternion.Y * quaternion.Y;
		float zz = quaternion.Z * quaternion.Z;

		float norm = xx + yy + zz + quaternion.W * quaternion.W;
		if (norm != 1)
		{
			quaternion = quaternion.GetNormalize();

			xx = quaternion.X * quaternion.X;
			yy = quaternion.Y * quaternion.Y;
			zz = quaternion.Z * quaternion.Z;
		}

		xx *= 2.f;
		yy *= 2.f;
		zz *= 2.f;

		float xy = 2.f * quaternion.X * quaternion.Y;
		float xz = 2.f * quaternion.X * quaternion.Z;
		float xw = 2.f * quaternion.X * quaternion.W;

		float yz = 2.f * quaternion.Y * quaternion.Z;
		float yw = 2.f * quaternion.Y * quaternion.W;

		float zw = 2.f * quaternion.Z * quaternion.W;

		result.raw[0] = 1.f - yy - zz;
		result.raw[4] = xy - zw;
		result.raw[8] = xz + yw;

		result.raw[1] = xy + zw;
		result.raw[5] = 1.f - xx - zz;
		result.raw[9] = yz - xw;

		result.raw[2] = xz - yw;
		result.raw[6] = yz + xw;
		result.raw[10] = 1.f - xx - yy;

		result.raw[15] = 1.f;

		return result;
	}

	//glm rotate order Z -> X -> Y
	Matrix4 Matrix4::Rotation(Radian x, Radian y, Radian z)
	{
		Matrix4 result;

		float cosx = cos(x);
		float cosy = cos(y);
		float cosz = cos(z);
		float sinx = sin(x);
		float siny = sin(y);
		float sinz = sin(z);

		result.raw[0] = cosy * cosz + -sinx * siny * sinz;
		result.raw[1] = cosy * sinz + sinx * siny * cosz;
		result.raw[2] = -cosx * siny;

		result.raw[4] = -cosx * sinz;
		result.raw[5] = cosx * cosz;
		result.raw[6] = sinx;

		result.raw[8] = siny * cosz + sinx * cosy * sinz;
		result.raw[9] = siny * sinz + -sinx * cosy * cosz;
		result.raw[10] = cosx * cosy;

		result.raw[15] = 1.f;

		return result;
	}

	Matrix4 Matrix4::Rotation(const Vector3& vec, bool radian)
	{
		if (radian)
		{
			return Rotation(Radian(vec.x), Radian(vec.y), Radian(vec.z));
		}
		else
		{
			return Rotation(Degree(vec.x), Degree(vec.y), Degree(vec.z));
		}
	}

	Matrix4 Matrix4::Scaling(float x, float y, float z)
	{
		Matrix4 result;

		result.raw[0] = x;
		result.raw[5] = y;
		result.raw[10] = z;
		result.raw[15] = 1.f;

		return result;
	}

	Matrix4 Matrix4::Scaling(const Vector3& vec)
	{
		Matrix4 result;

		result.raw[0] = vec.x;
		result.raw[5] = vec.y;
		result.raw[10] = vec.z;
		result.raw[15] = 1.f;

		return result;
	}

	Matrix4 Matrix4::Translation(float x, float y, float z)
	{
		Matrix4 result = Identity();

		result.raw[12] = x;
		result.raw[13] = y;
		result.raw[14] = z;

		return result;
	}

	Matrix4 Matrix4::Translation(const Vector3& vec)
	{
		Matrix4 result = Identity();

		result.raw[12] = vec.x;
		result.raw[13] = vec.y;
		result.raw[14] = vec.z;

		return result;
	}

	bool Matrix4::operator==(const Matrix4& other) const
	{
		if (this == &other) return true;

		for (int i = 0; i < 16; i++)
			if (raw[i] != other.raw[i])
				return false;

		return true;
	}

	Matrix4 Matrix4::operator*(Matrix4 const& other) const
	{
		Matrix4 result;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				for (int a = 0; a < 4; a++)
				{
					result[row][col] += (*this)[a][col] * other[row][a];
				}
			}
		}

		return result;
	}

	Matrix4& Matrix4::operator*=(Matrix4 const& other)
	{
		Matrix4 result;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				for (int a = 0; a < 4; a++)
				{
					result[row][col] += (*this)[a][col] * other[row][a];
				}
			}
		}

		*this = result;

		return *this;
	}

	Vector4 Matrix4::operator*(Vector4 const& other) const
	{
		Vector4 result;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				result[col] += (*this)[row][col] * other[row];
			}
		}

		return result;
	}

	Vector4 operator*(Vector4 const& otherVec, Matrix4 const& thisMat)
	{
		Vector4 result;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				result[row] += thisMat[row][col] * otherVec[col];
			}
		}

		return result;
	}

	float Matrix4::Determinant() const
	{
		float d = 0;

		//{
		//	for (int i = 0; i < 3; i++)
		//		d = d + (this[0][i] * (this[1][(i + 1) % 4] * this[2][(i + 2) % 4] - this[1][(i + 2) % 4] * this[2][(i + 1) % 4]));
		//}

		//0		1	2	3
		//4		5	6	7
		//8		9	10	11
		//12	13	14	15

		//+a		-b	+c	-d
		//+e		-f	+g	-h
		//+i		-j	+k	-l
		//+m		-n	+o	-p

		{
			Matrix4 inv(0.f);

			inv.raw[0] = this->raw[5] * this->raw[10] * this->raw[15] -
				this->raw[5] * this->raw[11] * this->raw[14] -
				this->raw[9] * this->raw[6] * this->raw[15] +
				this->raw[9] * this->raw[7] * this->raw[14] +
				this->raw[13] * this->raw[6] * this->raw[11] -
				this->raw[13] * this->raw[7] * this->raw[10];

			inv.raw[4] = -this->raw[4] * this->raw[10] * this->raw[15] +
				this->raw[4] * this->raw[11] * this->raw[14] +
				this->raw[8] * this->raw[6] * this->raw[15] -
				this->raw[8] * this->raw[7] * this->raw[14] -
				this->raw[12] * this->raw[6] * this->raw[11] +
				this->raw[12] * this->raw[7] * this->raw[10];

			inv.raw[8] = this->raw[4] * this->raw[9] * this->raw[15] -
				this->raw[4] * this->raw[11] * this->raw[13] -
				this->raw[8] * this->raw[5] * this->raw[15] +
				this->raw[8] * this->raw[7] * this->raw[13] +
				this->raw[12] * this->raw[5] * this->raw[11] -
				this->raw[12] * this->raw[7] * this->raw[9];

			inv.raw[12] = -this->raw[4] * this->raw[9] * this->raw[14] +
				this->raw[4] * this->raw[10] * this->raw[13] +
				this->raw[8] * this->raw[5] * this->raw[14] -
				this->raw[8] * this->raw[6] * this->raw[13] -
				this->raw[12] * this->raw[5] * this->raw[10] +
				this->raw[12] * this->raw[6] * this->raw[9];

			inv.raw[1] = -this->raw[1] * this->raw[10] * this->raw[15] +
				this->raw[1] * this->raw[11] * this->raw[14] +
				this->raw[9] * this->raw[2] * this->raw[15] -
				this->raw[9] * this->raw[3] * this->raw[14] -
				this->raw[13] * this->raw[2] * this->raw[11] +
				this->raw[13] * this->raw[3] * this->raw[10];

			inv.raw[5] = this->raw[0] * this->raw[10] * this->raw[15] -
				this->raw[0] * this->raw[11] * this->raw[14] -
				this->raw[8] * this->raw[2] * this->raw[15] +
				this->raw[8] * this->raw[3] * this->raw[14] +
				this->raw[12] * this->raw[2] * this->raw[11] -
				this->raw[12] * this->raw[3] * this->raw[10];

			inv.raw[9] = -this->raw[0] * this->raw[9] * this->raw[15] +
				this->raw[0] * this->raw[11] * this->raw[13] +
				this->raw[8] * this->raw[1] * this->raw[15] -
				this->raw[8] * this->raw[3] * this->raw[13] -
				this->raw[12] * this->raw[1] * this->raw[11] +
				this->raw[12] * this->raw[3] * this->raw[9];

			inv.raw[13] = this->raw[0] * this->raw[9] * this->raw[14] -
				this->raw[0] * this->raw[10] * this->raw[13] -
				this->raw[8] * this->raw[1] * this->raw[14] +
				this->raw[8] * this->raw[2] * this->raw[13] +
				this->raw[12] * this->raw[1] * this->raw[10] -
				this->raw[12] * this->raw[2] * this->raw[9];

			inv.raw[2] = this->raw[1] * this->raw[6] * this->raw[15] -
				this->raw[1] * this->raw[7] * this->raw[14] -
				this->raw[5] * this->raw[2] * this->raw[15] +
				this->raw[5] * this->raw[3] * this->raw[14] +
				this->raw[13] * this->raw[2] * this->raw[7] -
				this->raw[13] * this->raw[3] * this->raw[6];

			inv.raw[6] = -this->raw[0] * this->raw[6] * this->raw[15] +
				this->raw[0] * this->raw[7] * this->raw[14] +
				this->raw[4] * this->raw[2] * this->raw[15] -
				this->raw[4] * this->raw[3] * this->raw[14] -
				this->raw[12] * this->raw[2] * this->raw[7] +
				this->raw[12] * this->raw[3] * this->raw[6];

			inv.raw[10] = this->raw[0] * this->raw[5] * this->raw[15] -
				this->raw[0] * this->raw[7] * this->raw[13] -
				this->raw[4] * this->raw[1] * this->raw[15] +
				this->raw[4] * this->raw[3] * this->raw[13] +
				this->raw[12] * this->raw[1] * this->raw[7] -
				this->raw[12] * this->raw[3] * this->raw[5];

			inv.raw[14] = -this->raw[0] * this->raw[5] * this->raw[14] +
				this->raw[0] * this->raw[6] * this->raw[13] +
				this->raw[4] * this->raw[1] * this->raw[14] -
				this->raw[4] * this->raw[2] * this->raw[13] -
				this->raw[12] * this->raw[1] * this->raw[6] +
				this->raw[12] * this->raw[2] * this->raw[5];

			inv.raw[3] = -this->raw[1] * this->raw[6] * this->raw[11] +
				this->raw[1] * this->raw[7] * this->raw[10] +
				this->raw[5] * this->raw[2] * this->raw[11] -
				this->raw[5] * this->raw[3] * this->raw[10] -
				this->raw[9] * this->raw[2] * this->raw[7] +
				this->raw[9] * this->raw[3] * this->raw[6];

			inv.raw[7] = this->raw[0] * this->raw[6] * this->raw[11] -
				this->raw[0] * this->raw[7] * this->raw[10] -
				this->raw[4] * this->raw[2] * this->raw[11] +
				this->raw[4] * this->raw[3] * this->raw[10] +
				this->raw[8] * this->raw[2] * this->raw[7] -
				this->raw[8] * this->raw[3] * this->raw[6];

			inv.raw[11] = -this->raw[0] * this->raw[5] * this->raw[11] +
				this->raw[0] * this->raw[7] * this->raw[9] +
				this->raw[4] * this->raw[1] * this->raw[11] -
				this->raw[4] * this->raw[3] * this->raw[9] -
				this->raw[8] * this->raw[1] * this->raw[7] +
				this->raw[8] * this->raw[3] * this->raw[5];

			inv.raw[15] = this->raw[0] * this->raw[5] * this->raw[10] -
				this->raw[0] * this->raw[6] * this->raw[9] -
				this->raw[4] * this->raw[1] * this->raw[10] +
				this->raw[4] * this->raw[2] * this->raw[9] +
				this->raw[8] * this->raw[1] * this->raw[6] -
				this->raw[8] * this->raw[2] * this->raw[5];

			d = this->raw[0] * inv.raw[0] + this->raw[1] * inv.raw[4] + this->raw[2] * inv.raw[8] + this->raw[3] * inv.raw[12];
		}

		return d;
	}

	Matrix4 Matrix4::GetTranspose() const
	{
		Matrix4 result;

		result[0] = this->col(0);
		result[1] = this->col(1);
		result[2] = this->col(2);
		result[3] = this->col(3);

		return result;
	}

	Matrix4 Matrix4::GetInverse() const
	{
		Matrix4 result(0.f);
		float det = this->Determinant();

		if (det == 0)
			return result;

		det = 1.0f / det;

		for (int i = 0; i < 12; i++)
			result.raw[i] = this->raw[i] * det;

		result.Transpose();

		result[3][3] = 1.f;

		result *= Translation(-(*this)[3][0], -(*this)[3][1], -(*this)[3][2]);

		return result;
	}
}