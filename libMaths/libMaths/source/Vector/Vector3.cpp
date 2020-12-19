#include "Vector3.h"

#include "Core/CMath.h"
#include "Vector4.h"

namespace LibMath
{
	Vector3::Vector3(Vector4 const& other) :
		x(other.x/* / other.w*/), // glm conversion
		y(other.y/* / other.w*/),
		z(other.z/* / other.w*/)
	{}

	Vector3& Vector3::operator=(Vector4 const& other)
	{
		x = other.x/* / other.w*/; // glm conversion
		y = other.y/* / other.w*/;
		z = other.z/* / other.w*/;
		
		return *this;
	}


	float Vector3::Magnitude() const { return sqrt(x * x + y * y + z * z); }


	Radian Vector3::AngleBetween(Vector3 first, Vector3 second)
	{
		float firstSqSize = first.SquareMagnitude();
		if (firstSqSize != 1.f)
		{
			first /= sqrt(firstSqSize);
		}

		float secondSqSize = second.SquareMagnitude();
		if (secondSqSize != 1.f)
		{
			second /= sqrt(secondSqSize);
		}

		return acos(first.Dot(second));
	}


	Radian Vector3::TopDownAngleBetween(Vector3 first, Vector3 second)
	{
		first.y = 0.f;
		float firstSqMag = first.SquareMagnitude();
		if (firstSqMag != 1.f)
		{
			first /= sqrt(firstSqMag);
		}
		bool test = first.IsNormalize();

		second.y = 0.f;
		float secondSqMag = second.SquareMagnitude();
		if (secondSqMag != 1.f)
		{
			second /= sqrt(secondSqMag);
		}
		test = second.IsNormalize();

		float firstCrosssecondY = first.z * second.x - first.x * second.z;
		(void)firstCrosssecondY;
		(void)test;

		return acos(first.Dot(second)) * (firstCrosssecondY < 0 ? -1.f : 1.f);
	}
}