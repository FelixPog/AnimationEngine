#include "CORDIC.h"

#include "Core/AngleDefine.h"

namespace LibMath
{
	// lookup[idx] = tan0-1(1 / 2^idx)
	const float CORDIC::s_tanLookupGradian[CORDIC::s_maxPrecision] = { // todo change value to gradian value
		50.f,									// 1						// 1 / 2^0 = 1 / 1
		29.516723530086654835080215244948f,		// 0.5
		15.595826075473865092102577954626f,		// 0.25
		7.9166848321131084021703342680076f,		// 0.125
		3.9737048611081678118719765716209f,		// 0.0625
		1.988789564717854785722499751199f,		// 0.03125
		0.99463745579008257071246313675504f,	// 0.015625
		0.49734907873394785899372647269314f,	// 0.0078125
		0.24867833374282008347059282492288f,	// 0.00390625
		0.12433964118467431919497310781636f,	// 0.001953125
		0.06216987988200407574936014933804f,	// 0.0009765625
		0.03108494735222630511019902137426f,	// 0.00048828125
		0.01554247460251668292076403969373f,	// 0.000244140625
		0.0077712374170587982861387703198f,		// 0.0001220703125
		0.00388561872300445673160308171196f,	// 0.00006103515625
		0.00194280936331161057953431927131f,	// 0.000030517578125
		9.7140468188197806695769651585832e-4f,	// 0.0000152587890625
		4.8570234096926063064247597981497e-4f,	// 0.00000762939453125
		2.4285117048816426496715428676415e-4f,	// 0.000003814697265625
		1.2142558524452387618933114397731e-4f,	// 0.0000019073486328125
		6.0712792622317156057885274047066e-5f	// 0.00000095367431640625	// 1 / 2^20 = 1 / 1,048,576
	};



	float CORDIC::acos_9(float cosValue)
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

		return AngleOfCos(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], QUARTER_CIRCLE_GRADIAN, s_tanLookupGradian);
	}

	float CORDIC::asin_9(float sinValue)
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

		return AngleOfSin(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], s_tanLookupGradian);
	}

	float CORDIC::atan_9(float tanValue)
	{
		if (tanValue == 0)
		{
			return 0;
		}

		float sinValue = tanValue / sqrt(tanValue * tanValue + 1.f);
		float cosValue = 1 / sqrt(tanValue * tanValue + 1.f);

		return AngleOfSin(cosValue / s_cosLookup[s_precision - 1], sinValue / s_cosLookup[s_precision - 1], s_tanLookupGradian);
	}

	float CORDIC::cos_9(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_GRADIAN);

		if (targetAngle == 0)
		{
			return 1.f;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_GRADIAN, HALF_CIRCLE_GRADIAN, s_tanLookupGradian);

		return cos * s_cosLookup[s_precision - 1];
	}

	float CORDIC::sin_9(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_GRADIAN);

		if (targetAngle == 0)
		{
			return 0.f;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_GRADIAN, HALF_CIRCLE_GRADIAN, s_tanLookupGradian);

		return sin * s_cosLookup[s_precision - 1];
	}

	float CORDIC::tan_9(float targetAngle)
	{
		targetAngle = Clamp(targetAngle, CIRCLE_GRADIAN);

		if (targetAngle == 0)
		{
			return 0.f;
		}
		if (targetAngle == 90 || targetAngle == 270)
		{
			return NaN;
		}

		auto [cos, sin] = PositionOf(targetAngle, QUARTER_CIRCLE_GRADIAN, HALF_CIRCLE_GRADIAN, s_tanLookupGradian);

		return sin / cos;
	}
}