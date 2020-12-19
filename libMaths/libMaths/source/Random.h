#pragma once
#include <random>
#include <cstdlib> //include srand(), rand(), RAND_MAX
#include "Vector/Vector3.h"

namespace LibMath
{
	struct Vector3;
	struct Radian;
	
	class Random
	{
	public:

		/**
		 * @brief Default constructor. It will initialize the random with a seed based on the current time.
		 */
		Random();

		/**
		 * @brief Constructor by copy. It will initialize the random with the same seed as the other Random object.
		 * @param other	an other object of class Random.
		 */
		Random(const Random& other) = default;

		/**
		* @brief Equal operator. It will get the seed of the other Random object to setup the random.
		* @param other an other object of class Random.
		* @return Actual Random object.
		*/
		Random& operator=(const Random& other) = default;

		/**
		* @brief Creates and initializes a new Random with the specified seed value.
		* @param seed an unsigned int on which the random will be based.
		*/
		Random(unsigned int seed);

		/**
		* @brief Default destructor.
		*/
		~Random() = default;

		/**
		* @brief Returns the current seed.
		* @return The seed of the Random object.
		*/
		[[nodiscard]] unsigned int GetSeed() const;

		/**
		* @brief Changes the seed of the random for the given seed.
		* @param seed an unsigned int on which the random will be based.
		*/
		void MutateSeed(unsigned int seed);

		/**
		* @brief Changes the seed of the random for a seed based on the current time.
		*/
		void MutateSeed();

		/**
		* @brief Returns a random int between 0 and INT_MAX.
		* @return The random int generated.
		*/
		int RandomInt();

		/**
		* @brief Returns a random int in a given range (bounds included).
		* @param minInt the int for the lower bound of the range (with default = 0).
		* @param maxInt the int for the upper bound of the range (with default = INT_MAX).
		* @return The random int generated in the given range.
		*/
		int RandomIntInRange(int minInt = 0.f, int maxInt = INT_MAX);

		/**
		* @brief Returns a random float between 0 and FLT_MAX.
		* @return The random float generated
		*/
		float RandomFloat();

		/**
		* @brief Returns a random float in a given range (bounds included).
		* @param minFloat is the float for the lower bound of the range (with default = 0)
		* @param maxFloat is the float for the upper bound of the range (with default = FLT_MAX).
		* @return The random float generated in the given range.
		*/
		float RandomFloatInRange(float minFloat = 0.f, float maxFloat = FLT_MAX);

		/**
		* @brief Returns a random vector of unit size.
		* @return The random unit vector3 generated.
		*/
		Vector3 RandomUnitVector();

		/**
		* @brief Returns a random point in a given circle.
		* @param radius the float for the radius of the circle in witch the point will be generated
		* @param center the point (in vector3) for the center of this circle (with default value (0, 0, 0).
		* @return The random point (in Vector3) generated in the given circle.
		*/
		Vector3 RandomPointInCircle(float radius = 0.f, Vector3 center = {0.f, 0.f, 0.f});

		
		//Vector3 RandomPointInCone(Vector3 const& Dir, Degree ConeHalfAngleDeg);

	private:
		
		/**
		 * @brief an unsigned int on which the random will be based
		 */
		unsigned int m_seed;

		/**
		 * @brief defines bounds to generate a int
		 */
		std::uniform_int_distribution<int> m_intDistribution;
		
		/**
		 * @brief defines bounds to generate a float
		 */
		std::uniform_real_distribution<float> m_floatDistribution;

		/**
		 * @brief the random generator (works with a seed)
		 */
		std::mt19937 m_randomEngine;
		
	};

}
