#include "Random.h"

#include <chrono>

#include <iostream>

#include "Core/Angle.h" //include PI
#include "Core/CMath.h" //include sqrt(float)

namespace LibMath
{

	Random::Random()
	{
		m_seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
		m_randomEngine.seed(m_seed);

		m_intDistribution = std::uniform_int_distribution<int>(0, INT_MAX);
		m_floatDistribution = std::uniform_real_distribution<float>(0.f, FLT_MAX);
	}

	Random::Random(unsigned int seed):
	m_seed(seed)
	{
		m_randomEngine.seed(m_seed);

		m_intDistribution = std::uniform_int_distribution<int>(0, INT_MAX);
		m_floatDistribution = std::uniform_real_distribution<float>(0.f, FLT_MAX);
	}

	unsigned int Random::GetSeed() const
	{
		return m_seed;
	}

	void Random::MutateSeed(unsigned int seed)
	{
		m_seed = seed;
		m_randomEngine.seed(m_seed);
	}

	void Random::MutateSeed()
	{
		MutateSeed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	}

	int Random::RandomInt()
	{
		return m_intDistribution(m_randomEngine);
	}

	int Random::RandomIntInRange(int minInt, int maxInt)
	{
		if (minInt == maxInt)
		{
			return minInt;
		}

		if (minInt > maxInt)
		{
			const int buffer = maxInt;
			maxInt = minInt;
			minInt = buffer;
		}
		
		const std::uniform_int_distribution<int> distribution(minInt, maxInt);
		
		return distribution(m_randomEngine);
	}

	float Random::RandomFloat()
	{
		return m_floatDistribution(m_randomEngine);
	}

	float Random::RandomFloatInRange(float minFloat, float maxFloat)
	{
		if(minFloat == maxFloat)
		{
			return minFloat;
		}

		if(minFloat > maxFloat)
		{
			const float buffer = maxFloat;
			maxFloat = minFloat;
			minFloat = buffer;
		}

		const std::uniform_real_distribution<float> distribution(minFloat, maxFloat);

		return distribution(m_randomEngine);
	}

	Vector3 Random::RandomUnitVector()
	{
		Vector3 unitVector;

		unitVector.x = RandomFloatInRange(0.f, 100.f);
		unitVector.y = RandomFloatInRange(0.f, 100.f);
		unitVector.z = RandomFloatInRange(0.f, 100.f);

		unitVector.Normalize();

		return unitVector;
	}

	Vector3 Random::RandomPointInCircle(float radius, Vector3 center)
	{
		if(radius <= 0.f)
		{
			return center;
		}
		
		const float value = RandomFloatInRange(0.f, 1.f);
		const float a = value * 2 * PI;
		const float r = radius * sqrt(value);
		
		const float x = center.x + r * cos(Radian(a));
		const float y = center.y + r * sin(Radian(a));

		const Vector3 point(x, y, center.z);

		return point;
	}

	//TODO Vector3 Random::RandomPointInCone(Vector3 const& Dir, Degree ConeHalfAngleDeg)
	//Vector3 Random::RandomPointInCone(Vector3 const& Dir, Degree ConeHalfAngleDeg)
	//{
	//	Vector3 randomDirVector;

	//	randomDirVector.x = RandomFloat() * (1 - cos(ConeHalfAngleDeg)) + cos(ConeHalfAngleDeg);
	//	
	//	float value = randomDirVector.x * randomDirVector.x - 1;
	//	if(value < 0)
	//	{
	//		value = 0.00001;
	//	}
	//	float r = sqrt(value);
	//	float randomAngle = 2 * PI * RandomFloat();
	//	Degree randomAngleDeg(randomAngle);
	//	
	//	randomDirVector.y = r * sin(randomAngleDeg);
	//	randomDirVector.z = r * cos(randomAngleDeg);

	//	//TO DO: Rotate randomDirVector to turn x axis to be Dir
	//	
	//	return randomDirVector;
	//}

}