#pragma once

#include "Core/CMath.h"

namespace LibMath
{
	//https://www.youtube.com/watch?v=PalPWv0fU-s
	/**
	* CORDIC is an algorithm to approximate sin and cos of an angle.
	* <p>
	* The following suffix will be use in this implementation of CORDIC :
	* <ul>
	* <li>_0 -> degree
	* <li>_r -> radian
	* <li>_9 -> gradian
	* </ul>
	* <p>
	* The theory behind CORDIC is that given a known point (P = [1, 0] at 0_r). I
	* can do a binary search by rotating the vector a given amount of step either
	* clockwise or counter-clockwise in order to get as close as possible from the
	* wanted angle if i am looking for sin() or as close as possible from the wanted
	* position if i am looking for asin() or acos().
	* <p>
	* Given that (<~ means about equal but the rhs is a bit greater) :
	* <ul>
	* <li>tan_0(45) = 1
	* <li>tan_0(45 / 2) <~ 1/2
	* <li>tan_0((45 / 2) / 2) <~ tan_0(45 / 2) / 2
	* <li>tan_0(((45 / 2) / 2) / 2) <~ tan_0((45 / 2) / 2) / 2
	* <li>...
	* </ul>
	* <p>
	* Than I can use the angle atan_0(1 / 2^-n) as a step size where n means I am
	* computing the n-th step. This work as a binary search because each step is
	* greater than half the last one but not greanter than the last step itself.
	* In other word because (lastStep > currentStep && currentStep > lastStep / 2)
	* My approximaion will converge toward the requested value. So I precompute and
	* store the following values :
	* <ul>atan_0(1 / 2^0) = 45_0
	* <ul>atan_0(1 / 2^1) = 26.565..._0
	* <ul>atan_0(1 / 2^2) = 14.036..._0
	* <ul>atan_0(1 / 2^3) = 7.125..._0
	* <li>...
	* </ul>
	* <p>
	* The counter-clockwise rotation matrix in 2D is the following :
	* <p>
	* [ cos  -sin ] -> cos [ cos/cos  -sin/cos ] -> cos [  1   -tan ]
	* [ sin   cos ]        [ sin/cos   cos/cos ]        [ tan    1  ]
	* <p>
	* The clockwise rotation matrix in 2D is the following :
	* <p>
	* [  cos  sin ] -> -cos [  cos/-cos  sin/-cos ] -> cos * -[  1   -tan ]
	* [ -sin  cos ]			[ -sin/-cos  cos/-cos ]           [ tan    1  ]
	* <p>
	* Since adding rotation is multiplying matrices I can accumulate all my rotaion
	* in a single formula :
	* <p>
	* cos1 * cos2 * cos3 * ... ±[  1   -tan ] * ±[  1   -tan ] * ±[   1   tan ] * ...
	*                           [ tan    1  ]    [ tan    1  ]    [ -tan   1  ]
	* <p>
	* Notice that [cos1 * cos2 * cos3 * ...] are always positive [cos] and therefore
	* the whole [cos] mutiplication result in a constant that can also be precompute
	* <p>
	* Finaly by rotating with the angles precompute ealier in my binary search
	* instead of rotating halfway as a standard binary search would suggest I
	* already know the value of tan(x) so my final approximation formuala is :
	* <p>
	* cosConstant * ±[   1   -2^-0 ] * ±[  1    -2^-1 ] * ±[  1    -2^-2 ] * ...
	*                [ 1^-0    1   ]    [ 2^-1    1   ]    [ 2^-2    1   ]
	* <p>
	* example sin_0(245) : starting point is in the 3rd quadran so I will start with
	* the known point P = [-1, 0] at 180_0.
	* <p>
	* sin_0(245) -> 245 - 180 = 0 + 45 + 26.565 - 14.036 + 7.125 - 3.576 - ...
	* <p>
	* P = cosConstant * rot(atan(1)) * rot(atan(1/2)) * (-)rot(atan(1/4)) * ...
	* <p>
	* sin_0(245) = P.y;
	* 
	*/
	class CORDIC
	{
	public:
		~CORDIC() = delete;

		static float Clamp(float angle, float const fullCircle) { return angle >= fullCircle ? fmod(angle, fullCircle) : angle + ceil((-angle) / fullCircle) * fullCircle; }
		static void SetPrecision(int precision) { s_precision = precision < 0 ? 0 : precision > s_maxPrecision ? s_maxPrecision : precision; }

		static float acos_0(float degree);
		static float asin_0(float degree);
		static float atan_0(float degree);

		static float cos_0(float degree);
		static float sin_0(float degree);
		static float tan_0(float degree);


		static float acos_r(float radian);
		static float asin_r(float radian);
		static float atan_r(float radian);

		static float cos_r(float radian);
		static float sin_r(float radian);
		static float tan_r(float radian);


		static float cos_9(float radian);
		static float sin_9(float radian);
		static float tan_9(float radian);

		static float acos_9(float radian);
		static float asin_9(float radian);
		static float atan_9(float radian);

	private:

		struct Coodinate { float cos, sin; };
		static Coodinate PositionOf(float targetAngle, float quarterCircle, float halfCircle, float const* tanLookup);
		static float AngleOfSin(float cosValue, float sinValue, float const* tanLookup);
		static float AngleOfCos(float targetCos, float sinValue, float quarterCircle, float const* tanLookup);

		inline static int s_precision = 21;

		static int const s_maxPrecision = 21;

		static float const s_tanLookupDegree[s_maxPrecision];
		static float const s_tanLookupRadian[s_maxPrecision];
		static float const s_tanLookupGradian[s_maxPrecision];

		//inline static float const s_cosLookup = 0.60725293500897330505728452408154f;
		inline static float const s_cosLookup[s_maxPrecision] = {
			0.70710678118654752440084436210485f,
			0.63245553203367586639977870888655f,
			0.61357199107789634960780908775804f,
			0.60883391251775242102211350754739f,
			0.60764825625616820092932166030953f,
			0.60735177014129595905351239038777f,
			0.60727764409352599904691536733759f,
			0.60725911229889273006029454182251f,
			0.60725447933256232971739808632516f,
			0.60725332108987516334343519856377f,
			0.60725303152913433540228465466153f,
			0.60725295913894481363035179763757f,
			0.60725294104139716351297018642411f,
			0.60725293651701023412897124207974f,
			0.60725293538591350072955560274528f,
			0.60725293510313931731386319806955f,
			0.60725293503244577145582519095909f,
			0.60725293501477238499105850755991f,
			0.60725293501035403837485076285877f,
			0.60725293500924945172079782206777f,
			0.60725293500897330505728452408154f};

	};
	
	inline CORDIC::Coodinate CORDIC::PositionOf(float targetAngle, float quarterCircle, float halfCircle, float const* tanLookup)
	{
		// Select starting point P
		float sin = 1.f;
		float cos = 0.f;
		float currentAngle = quarterCircle;
		float prevCos;

		if (targetAngle > halfCircle)
		{
			sin = -1.f;
			currentAngle += halfCircle;
		}

		// Rotate point P s_precision times
		for (int i = 0; i < s_precision; i++)
		{
			prevCos = cos;
			if (currentAngle < targetAngle)
			{
				currentAngle += tanLookup[i];
				cos -= ldexpf(sin, -i);
				sin += ldexpf(prevCos, -i);
			}
			else
			{
				currentAngle -= tanLookup[i];
				cos += ldexpf(sin, -i);
				sin -= ldexpf(prevCos, -i);
			}
		}

		return { cos, sin };
	}

	inline float CORDIC::AngleOfSin(float cosValue, float sinValue, float const* tanLookup)
	{
		// Select starting point P
		float currentAngle = 0.f;
		float prevCos;

		// Un-rotate point P s_precision times
		for (int i = 0; i < s_precision; i++)
		{
			prevCos = cosValue;
			if (sinValue > 0.f)
			{
				currentAngle += tanLookup[i];		// Add angle
				cosValue += ldexpf(sinValue, -i);	// remove rotation
				sinValue -= ldexpf(prevCos, -i);
			}
			else
			{
				currentAngle -= tanLookup[i];
				cosValue -= ldexpf(sinValue, -i);
				sinValue += ldexpf(prevCos, -i);
			}
		}

		return currentAngle;
	}

	inline float CORDIC::AngleOfCos(float cosValue, float sinValue, float quarterCircle, float const* tanLookup)
	{
		// Select starting point P
		float currentAngle = quarterCircle;
		float prevCos;

		// Un-rotate point P s_precision times
		for (int i = 0; i < s_precision; i++)
		{
			prevCos = cosValue;
			if (cosValue < 0.f)
			{
				currentAngle += tanLookup[i];		// Add angle
				cosValue += ldexpf(sinValue, -i);	// remove rotation
				sinValue -= ldexpf(prevCos, -i);
			}
			else
			{
				currentAngle -= tanLookup[i];
				cosValue -= ldexpf(sinValue, -i);
				sinValue += ldexpf(prevCos, -i);
			}
		}

		return currentAngle;
	}
}