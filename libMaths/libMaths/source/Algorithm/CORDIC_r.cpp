#include "CORDIC.h"

#include "Core/AngleDefine.h"

namespace LibMath
{
	// lookup[idx] = tanr-1(1 / 2^idx)
	const float CORDIC::s_tanLookupRadian[CORDIC::s_maxPrecision] = {
		0.78539816339744830961566084581988f,	// 1						// 1 / 2^0 = 1 / 1
		0.46364760900080611621425623146121f,	// 0.5
		0.24497866312686415417208248121128f,	// 0.25
		0.12435499454676143503135484916387f,	// 0.125
		0.06241880999595734847397911298551f,	// 0.0625
		0.03123983343026827625371174489249f,	// 0.03125
		0.01562372862047683080280152125657f,	// 0.015625
		0.0078123410601011112964633918422f,		// 0.0078125
		0.00390623013196697182762866531142f,	// 0.00390625
		0.00195312251647881868512148262508f,	// 0.001953125
		9.7656218955931943040343019971729e-4f,	// 0.0009765625
		4.8828121119489827546923962564485e-4f,	// 0.00048828125
		2.4414062014936176401672294325966e-4f,	// 0.000244140625
		1.2207031189367020423905864611796e-4f,	// 0.0001220703125
		6.1035156174208775021662569173829e-5f,	// 0.00006103515625
		3.0517578115526096861825953438536e-5f,	// 0.000030517578125
		1.5258789061315762107231935812698e-5f,	// 0.0000152587890625
		7.6293945311019702633884823401051e-6f,	// 0.00000762939453125
		3.814697265606496282923075616373e-6f,	// 0.000003814697265625
		1.9073486328101870353653693059172e-6f,	// 0.0000019073486328125
		9.5367431640596087942067068992311e-7f	// 0.00000095367431640625	// 1 / 2^20 = 1 / 1,048,576
	};



	float CORDIC::acos_r(float cosValue)
	{
		if (-1 > cosValue || cosValue > 1)
		{
			return NaN;
		}

		if (cosValue == 1.f)
		{
			return 0.f;
		}

		float sinValue = sqrt(1 - cosValue * cosValue);

		return AngleOfCos(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], QUARTER_CIRCLE_RADIAN, s_tanLookupRadian);
	}

	float CORDIC::asin_r(float sinValue)
	{
		if (-1 > sinValue || sinValue > 1)
		{
			return NaN;
		}

		if (sinValue == 0.f)
		{
			return 0.f;
		}

		float cosValue = sqrt(1 - sinValue * sinValue);

		return AngleOfSin(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], s_tanLookupRadian);
	}

	float CORDIC::atan_r(float tanValue)
	{
		if (tanValue == 0)
		{
			return 0;
		}

		float sinValue = tanValue / sqrt(tanValue * tanValue + 1.f);
		float cosValue = 1 / sqrt(tanValue * tanValue + 1.f);

		return AngleOfSin(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], s_tanLookupRadian);
	}

	float CORDIC::cos_r(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_RADIAN);

		if (targetAngle == 0)
		{
			return 1.f;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_RADIAN, HALF_CIRCLE_RADIAN, s_tanLookupRadian);

		return cos * s_cosLookup[s_precision - 1];
	}

	float CORDIC::sin_r(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_RADIAN);

		if (targetAngle == 0)
		{
			return 0.f;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_RADIAN, HALF_CIRCLE_RADIAN, s_tanLookupRadian);

		return sin * s_cosLookup[s_precision - 1];
	}

	float CORDIC::tan_r(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_RADIAN);

		if (targetAngle == 0)
		{
			return 0.f;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_RADIAN, HALF_CIRCLE_RADIAN, s_tanLookupRadian);

		return sin / cos;
	}
}