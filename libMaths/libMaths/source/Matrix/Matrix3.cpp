#include "Matrix3.h"

namespace LibMath
{
    Matrix3::Matrix3(const float& a, const float& b, const float& c, const float& d, const float& e, const float& f, const float& g, const float& h, const float& i)
    {
		m_row[0] = a;
		m_row[1] = b;
		m_row[2] = c;
		m_row[3] = d;
		m_row[4] = e;
		m_row[5] = f;
		m_row[6] = g;
		m_row[7] = h;
		m_row[8] = i;
    }

	Matrix3::Matrix3(const float& diagonalValue)
	{
		m_row[0] = diagonalValue;
		m_row[4] = diagonalValue;
		m_row[8] = diagonalValue;
	}

    Matrix3 Matrix3::ScaleMatrix(const float& x, const float& y)
    {
		Matrix3 result;

		result.m_row[0] = x;
		result.m_row[4] = y;
		result.m_row[8] = 1;

		return result;
    }

	Matrix3 Matrix3::Scale(const float& x, const float& y) const
	{
		Matrix3 result;

		result.m_row[0] = (*this).m_row[0] * x;
		result.m_row[1] = (*this).m_row[1] * x;
		result.m_row[2] = (*this).m_row[2] * x;
		result.m_row[3] = (*this).m_row[3] * y;
		result.m_row[4] = (*this).m_row[4] * y;
		result.m_row[5] = (*this).m_row[5] * y;
		result.m_row[6] = (*this).m_row[6];
		result.m_row[7] = (*this).m_row[7];
		result.m_row[8] = (*this).m_row[8];

		return result;
	}

	Matrix3 Matrix3::RotationMatrix(const Radian& rad)
	{
		Matrix3 result;

		const float co = cos(rad);
		const float si = sin(rad);

		result.m_row[0] = co;
		result.m_row[1] = si;
		result.m_row[2] = 0;

		result.m_row[3] = -si;
		result.m_row[4] = co;
		result.m_row[5] = 0;

		result.m_row[6] = 0;
		result.m_row[7] = 0;
		result.m_row[8] = 1;

		return result;
	}

	Matrix3 Matrix3::TranslationMatrix(const float& x, const float& y)
	{
		Matrix3 result = IdentityMatrix();

		result.m_row[6] = x;
		result.m_row[7] = y;

		return result;
	}

    Matrix3 Matrix3::Transpose() const
    {
		Matrix3 result = (*this);
		result[0][1] = (*this)[1][0];
		result[1][0] = (*this)[0][1];

		result[0][2] = (*this)[2][0];
		result[2][0] = (*this)[0][2];

		result[1][2] = (*this)[2][1];
		result[2][1] = (*this)[1][2];

		return result;
    }

    void Matrix3::Transpose(Matrix3& matrix)
    {
		matrix = matrix.Transpose();
    }

    float Matrix3::Determinant() const
	{
		return	(*this)[0][0] * ((*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1]) -
			    (*this)[1][0] * ((*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2]) +
			    (*this)[2][0] * ((*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2]);
    }

    Matrix3 Matrix3::Adjugate() const
    {
		Matrix3 result = (*this);
		result[0][0] = +((*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2]);
		result[1][0] = -((*this)[1][0] * (*this)[2][2] - (*this)[2][0] * (*this)[1][2]);
		result[2][0] = +((*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1]);
		result[0][1] = -((*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2]);
		result[1][1] = +((*this)[0][0] * (*this)[2][2] - (*this)[2][0] * (*this)[0][2]);
		result[2][1] = -((*this)[0][0] * (*this)[2][1] - (*this)[2][0] * (*this)[0][1]);
		result[0][2] = +((*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2]);
		result[1][2] = -((*this)[0][0] * (*this)[1][2] - (*this)[1][0] * (*this)[0][2]);
		result[2][2] = +((*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1]);

		return result;
    }

	Matrix3 Matrix3::Inverse() const
	{
		const float det = this->Determinant();
		if(det == 0.f)
		{
			return Matrix3();
		}

		return this->Adjugate()/det;
	}

	void Matrix3::Inverse(Matrix3& matrix)
	{
		matrix = matrix.Inverse();
	}

    Matrix3 Matrix3::Translate(const float& x, const float& y) const
    {
		return (*this) * TranslationMatrix(x, y);
    }

    Matrix3 Matrix3::Rotate(const Radian& rad) const
    {
		Matrix3 result;

		const float co = cos(rad);
		const float si = sin(rad);

		result.m_row[0] = (*this).m_row[0] * co + (*this).m_row[3] * si;
		result.m_row[1] = (*this).m_row[1] * co + (*this).m_row[4] * si;
		result.m_row[2] = (*this).m_row[2] * co + (*this).m_row[5] * si;

		result.m_row[3] = (*this).m_row[3] * co - (*this).m_row[0] * si;
		result.m_row[4] = (*this).m_row[4] * co - (*this).m_row[1] * si;
		result.m_row[5] = (*this).m_row[5] * co - (*this).m_row[2] * si;

		result.m_row[6] = (*this).m_row[6];
		result.m_row[7] = (*this).m_row[7];
		result.m_row[8] = (*this).m_row[8];

		return result;
    }

    bool Matrix3::operator==(const Matrix3& other) const
	{
		if (this == &other) return true;

		for (auto i = 0; i < 9; i++)
			if (m_row[i] != other.m_row[i])
				return false;

		return true;
	}

    Matrix3& Matrix3::operator+=(const Matrix3& other)
    {
		for (auto row = 0; row < 3; ++row)
		{
			for (auto col = 0; col < 3; ++col)
			{
				(*this)[row][col] += other[row][col];
			}
		}

		return (*this);
    }

	Matrix3& Matrix3::operator-=(Matrix3 const& other)
	{
		for (auto row = 0; row < 3; ++row)
		{
			for (auto col = 0; col < 3; ++col)
			{
				(*this)[row][col] -= other[row][col];
			}
		}

		return (*this);
	}

	Matrix3& Matrix3::operator*=(const Matrix3& other)
	{
		Matrix3 result;

		for (auto row = 0; row < 3; row++)
		{
			for (auto col = 0; col < 3; col++)
			{
				for (auto a = 0; a < 3; a++)
				{
					result[row][col] += (*this)[a][col] * other[row][a];
				}
			}
		}

		*this = result;

		return *this;
	}

	Matrix3& Matrix3::operator/=(const float& other)
	{
		for (auto row = 0; row < 3; row++)
		{
			for (auto col = 0; col < 3; col++)
			{
				(*this)[row][col] /= other;
			}
		}
		return (*this);
	}

	Matrix3& Matrix3::operator*=(const float& other)
	{
		for (auto row = 0; row < 3; row++)
		{
			for (auto col = 0; col < 3; col++)
			{
				(*this)[row][col] *= other;
			}
		}
		return (*this);
	}

	Matrix3 operator+(Matrix3 lhs, const Matrix3& rhs)
	{
		Matrix3 result;

		for (auto row = 0; row < 3; ++row)
		{
			for (auto col = 0; col < 3; ++col)
			{
				result[row][col] = lhs[row][col] + rhs[row][col];
			}
		}

		return result;
	}

    Matrix3 operator-(Matrix3 lhs, const Matrix3& rhs)
    {
		Matrix3 result;

		for (auto row = 0; row < 3; ++row)
		{
			for (auto col = 0; col < 3; ++col)
			{
				result[row][col] = lhs[row][col] - rhs[row][col];
			}
		}

		return result;
    }

    Matrix3 operator*(Matrix3 lhs, const Matrix3& rhs)
	{
		Matrix3 result;

		for (auto row = 0; row < 3; ++row)
		{
			for (auto col = 0; col < 3; ++col)
			{
				for (auto a = 0; a < 3; ++a)
				{
					result[row][col] += lhs[a][col] * rhs[row][a];
				}
			}
		}

		return result;
	}

    Matrix3 operator/(Matrix3 lhs, const float& rhs)
    {
		for(auto row = 0; row < 3; row++)
		{
		    for(auto col = 0; col < 3; col++)
		    {
				lhs[row][col] /= rhs;
		    }
		}
		return lhs;
    }

    Matrix3 operator*(Matrix3 lhs, const float& rhs)
    {
		Matrix3 result;
		for (auto row = 0; row < 3; row++)
		{
			for (auto col = 0; col < 3; col++)
			{
				result[row][col] = lhs[row][col] * rhs;
			}
		}
		return result;
    }
}
