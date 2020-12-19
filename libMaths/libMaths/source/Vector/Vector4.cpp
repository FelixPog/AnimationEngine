#include "Vector4.h"

#include "Core/CMath.h"
#include "Vector3.h"

namespace LibMath
{
	Vector4 Vector4::Direction(const Vector3& other)
	{
		return Vector4(other.x, other.y, other.z, 0.f);
	}

	Vector4 Vector4::Point(const Vector3& other)
	{
		return Vector4(other.x, other.y, other.z, 1.f);
	}

}
