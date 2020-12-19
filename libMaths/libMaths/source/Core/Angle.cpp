#include "Angle.h"

#include <Core/CMath.h>
#include <cmath>

namespace LibMath
{
	bool Degree::operator==(Radian other) const { return ApproxFloat(data, other.deg(), 0.000001f); }
	bool Degree::operator!=(Radian other) const { return !ApproxFloat(data, other.deg(), 0.000001f); }

	bool Radian::operator==(Degree other) const { return ApproxFloat(data, other.rad(), 0.000001f); }
	bool Radian::operator!=(Degree other) const { return !ApproxFloat(data, other.rad(), 0.000001f); }
	bool Radian::operator<=(Radian other) const { return (data < other.data || ApproxFloat(data, other.data, 0.000001f)); }
	bool Radian::operator>=(Radian other) const { return (data > other.data || ApproxFloat(data, other.data, 0.000001f)); }
	
	void Degree::Clamp() { data = data >= 0 ? fmod(data, CIRCLE_DEGREE) : data + ceilf(-data * CIRCLE_DEGREE_RECIPROCAL) * CIRCLE_DEGREE; }
	void Radian::Clamp() { data = data >= 0 ? fmod(data, CIRCLE_RADIAN) : data + ceilf(-data * CIRCLE_RADIAN_RECIPROCAL) * CIRCLE_RADIAN; }
	
	float cos(Angle const& angle) { return std::cos(angle.rad()); }
	float cos(Degree angle) { return std::cos(angle.rad()); }
	float cos(Radian angle) { return std::cos(angle.rad()); }

	float sin(Angle const& angle) { return std::sin(angle.rad()); }
	float sin(Degree angle) { return std::sin(angle.rad()); }
	float sin(Radian angle) { return std::sin(angle.rad()); }

	float tan(Angle const& angle) { return std::tan(angle.rad()); }
	float tan(Degree angle) { return std::tan(angle.rad()); }
	float tan(Radian angle) { return std::tan(angle.rad()); }

	Radian acos(float x) { return Radian(std::acos(x)); }
	Radian asin(float x) { return Radian(std::asin(x)); }
	Radian atan(float x) { return Radian(std::atan(x)); }
	Radian atan2(float y, float x) { return Radian(std::atan2(y, x)); }
}
