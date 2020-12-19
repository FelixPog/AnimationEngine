#include "CORDIC.h"

#include "Core/AngleDefine.h"

namespace LibMath
{
	// lookup[idx] = tan0-1(1 / 2^idx)
	const float CORDIC::s_tanLookupDegree[CORDIC::s_maxPrecision] = {
		45.f,									// 1						// 1 / 2^0 = 1 / 1
		26.565051177077989351572193720453f,		// 0.5
		14.036243467926478582892320159163f,		// 0.25
		7.1250163489017975619533008412068f,		// 0.125
		3.5763343749973510306847789144588f,		// 0.0625
		1.7899106082460693071502497760791f,		// 0.03125
		0.89517371021107431364121682307953f,	// 0.015625
		0.44761417086055307309435382542382f,	// 0.0078125
		0.22381050036853807512353354243059f,	// 0.00390625
		0.11190567706620688727547579703472f,	// 0.001953125
		0.05595289189380366817442413440423f,	// 0.0009765625
		0.02797645261700367459917911923683f,	// 0.00048828125
		0.01398822714226501462868763572436f,	// 0.000244140625
		0.00699411367535291845752489328782f,	// 0.0001220703125
		0.00349705685070401105844277354077f,	// 0.00006103515625
		0.00174852842698044952158088734418f,	// 0.000030517578125
		8.7426421369378026026192686427249e-4f,	// 0.0000152587890625
		4.3713210687233456757822838183347e-4f,	// 0.00000762939453125
		2.1856605343934783847043885808773e-4f,	// 0.000003814697265625
		1.0928302672007148857039802957958e-4f,	// 0.0000019073486328125
		5.464151336008544045209674664236e-5f	// 0.00000095367431640625	// 1 / 2^20 = 1 / 1,048,576
	};



	float CORDIC::acos_0(float cosValue)
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

		return AngleOfCos(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], QUARTER_CIRCLE_DEGREE, s_tanLookupDegree);
	}

	float CORDIC::asin_0(float sinValue)
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

		return AngleOfSin(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], s_tanLookupDegree);
	}

	float CORDIC::atan_0(float tanValue)
	{
		if (tanValue == 0)
		{
			return 0;
		}

		float sinValue = tanValue / sqrt(tanValue * tanValue + 1.f);
		float cosValue = 1 / sqrt(tanValue * tanValue + 1.f);

		return AngleOfSin(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], s_tanLookupDegree);
	}

	float CORDIC::cos_0(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_DEGREE);

		if (targetAngle == 0)
		{
			return 1.f;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_DEGREE, HALF_CIRCLE_DEGREE, s_tanLookupDegree);

		return cos * s_cosLookup[s_precision - 1];
	}

	float CORDIC::sin_0(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_DEGREE);

		if (targetAngle == 0)
		{
			return 0.f;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_DEGREE, HALF_CIRCLE_DEGREE, s_tanLookupDegree);

		return sin * s_cosLookup[s_precision - 1];
	}

	float CORDIC::tan_0(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_DEGREE);

		if (targetAngle == 0)
		{
			return 0.f;
		}
		if (targetAngle == 90 || targetAngle == 270)
		{
			return NaN;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_DEGREE, HALF_CIRCLE_DEGREE, s_tanLookupDegree);

		return sin / cos;
	}
}