#pragma once

#define DEGREE_TO_RADIAN(degree) ((degree) * ONE_DEGREE_IN_RADIAN)
#define RADIAN_TO_DEGREE(radian) ((radian) * ONE_RADIAN_IN_DEGREE)

namespace LibMath
{
	constexpr float PI = 3.1415926535897932384626433832795f;

	constexpr float EIGHTH_CIRCLE_RADIAN = PI / 4.f;
	constexpr float QUARTER_CIRCLE_RADIAN = PI / 2.f;
	constexpr float HALF_CIRCLE_RADIAN = PI;
	constexpr float CIRCLE_RADIAN = 2.f * PI;
	constexpr float CIRCLE_RADIAN_RECIPROCAL = 1.f / CIRCLE_RADIAN;
	constexpr float ONE_DEGREE_IN_RADIAN = (1.f / 180.f) * PI;
	constexpr float ONE_GRADIAN_IN_RADIAN = 0.005f * PI;

	constexpr float EIGHTH_CIRCLE_DEGREE = 45.f;
	constexpr float QUARTER_CIRCLE_DEGREE = 90.f;
	constexpr float HALF_CIRCLE_DEGREE = 180.f;
	constexpr float CIRCLE_DEGREE = 360.f;
	constexpr float CIRCLE_DEGREE_RECIPROCAL = 1.f / CIRCLE_DEGREE;
	constexpr float ONE_RADIAN_IN_DEGREE = (1.f / PI) * 180.f;
	constexpr float ONE_GRADIAN_IN_DEGREE = 0.9f;

	constexpr float EIGHTH_CIRCLE_GRADIAN = 50.f;
	constexpr float QUARTER_CIRCLE_GRADIAN = 100.f;
	constexpr float HALF_CIRCLE_GRADIAN = 200.f;
	constexpr float CIRCLE_GRADIAN = 400.f;
	constexpr float CIRCLE_GRADIAN_RECIPROCAL = 1.f / CIRCLE_GRADIAN;
	constexpr float ONE_RADIAN_IN_GRADIAN = (1.f / PI) * 200.f;
	constexpr float ONE_DEGREE_IN_GRADIAN = 10.f / 9.f;
}
