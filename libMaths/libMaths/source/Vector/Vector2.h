#pragma once
#include "Core/Angle.h"
#include "Core/CMath.h"
namespace LibMath
{
	/**
	* A structure to represent 2d vectors
	*/
	struct Vector2
	{
		/*
		* @name Coordinates
		*/
		/*@{*/
		float x = 0.f;/**< the x coordinate*/
		float y = 0.f;/**< the y coordinate*/
		/*@}*/

		/**
		* @brief Default constructor generate a vector (0,0)
		*/
		Vector2() = default;

		/**
		* @brief Default destructor
		*/
		~Vector2() = default;
		
		/**
		* @brief Default copy Constructor
		*
		* @param other 2D Vector to copy from.
		*/
		Vector2(const Vector2& other) = default;

		/**
		 * @brief Default assignment operator
		 * @param other Vector to copy
		 */
		Vector2& operator=(const Vector2& other) = default;
		
		/**
		* @brief Constructor initializing all components to a single float value.
		*
		* @param value Value to set all components to.
		*/
		Vector2(const float value) : x(value), y(value){}
		
		/**
		* @brief Constructor using initial values for each component.
		*
		* @param px X Coordinate.
		* @param py Y Coordinate.
		*/
		Vector2(const float px, const float py) : x(px), y(py) {}
		
		/*
		 * @brief Create a zero vector
		 * @return Vector(0.0f, 0.0f) 
		 */
		static Vector2 Zero() { return Vector2(0.f, 0.f); }

		
		/*
		 * @brief Create a vector one
		 * @return Vector(1.0f, 1.0f)
		 */
		static Vector2 One() { return Vector2(1.f, 1.f); }

		/*
		 * @brief Create a vector Up
		 * @return Vector(0.0f, 1.0f)
		 */
		static Vector2 Up() { return Vector2(0.f, 1.f); }

		/*
		 * @brief Create a vector Down
		 * @return Vector(0.0f, -1.0f)
		 */
		static Vector2 Down() { return Vector2(0.f, -1.f); }

		/*
		 * @brief Create a vector Right
		 * @return Vector(1.0f, 0.0f)
		 */
		static Vector2 Right() { return Vector2(1.f, 0.f); }

		/*
		 * @brief Create a vector Left
		 * @return Vector(-1.0f, 0.0f)
		 */
		static Vector2 Left() { return Vector2(-1.f, 0.f); }

		
		/**
		 * @brief Compare both vector with a tolerance (default tolerance is 1.192092896e-07F)
		 * 
		 * @param other Vector to compare with
		 * @param tolerance Tolerance between coordinates
		 * @return true if both vector are equal, false if not
		 */
		[[nodiscard]] bool Equals(const Vector2 & other, const float tolerance = MY_FLT_EPSILON) const { return Absolute(x - other.x) < tolerance && Absolute(y - other.y) < tolerance; }

		/**
		* @brief Check against another vector for equality.
		*
		* @param other The vector to check against.
		* @return true if the vectors are equal, false otherwise.
		*/
		bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }

		/**
		* @brief Check against another vector for inequality.
		*
		* @param other The vector to check against.
		* @return true if the vectors are not equal, false otherwise.
		*/
		bool operator!=(const Vector2& other) const { return !(*this == other); }


		//TODO Continue review
		
		/**
		 * @brief Compare two vector length
		 * @param other Second vector to compare
		 * @return True if the first vector is longer, false if not
		 */
		[[nodiscard]] bool IsLongerThan(const Vector2& other) const { return SquareMagnitude() > other.SquareMagnitude(); }

		/**
		 * @brief Compare two vector length
		 * @param other Second vector to compare
		 * @return True if the first vector is longer or equal, false if not
		 */
		[[nodiscard]] bool IsLongerOrEqualThan(const Vector2& other) const { return !this->IsShorterThan(other); }
		
		/**
		 * @brief Compare two vector length
		 * @param other Second vector to compare
		 * @return True if the first vector is shorter, false if not
		 */
		[[nodiscard]] bool IsShorterThan(const Vector2& other) const { return SquareMagnitude() < other.SquareMagnitude(); }

		/**
		 * @brief Compare two vector length
		 * @param other Second vector to compare
		 * @return True if the first vector is shorter or equal, false if not
		 */
		[[nodiscard]] bool IsShorterThanOrEqualThan(const Vector2& other) const { return !this->IsLongerThan(other); }

		
		/**
		* @brief Gets the result of component-wise addition of this and another vector.
		*
		* @param rhs The vector to add to this.
		* @return The result of vector addition.
		*/
		Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }

		/**
		* @brief Gets the result of component-wise subtraction of this by another vector.
		*
		* @param rhs The vector to subtract from this.
		* @return The result of vector subtraction.
		*/
		Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

		/**
		* @brief Multiplie the vector by three different value
		*
		* @param rhs Ratio to use
		* @return The result of multiplication.
		*/
		Vector2& operator*=(const Vector2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }

		/**
		* @brief Divide the vector by three different value
		*
		* @param rhs Ratio to use
		* @return The result of division.
		*/
		Vector2& operator/=(const Vector2& rhs);

		/** 
		* @brief Get a negated copy of the vector.
		* @param rhs The negated vector
		* @return A negated copy of the vector.
		*/
		friend Vector2 operator-(const Vector2& rhs) { return Vector2(-rhs.x, -rhs.y); }
		
		/**
		* @brief  Subtract two Vector2 together.
		* @param lhs Vector2 on the left side of the operator.
		* @param rhs Vector2 on the right side of the operator.
		* @return A Vector2 holding the sum of the subtraction
		*/
		friend Vector2 operator-(Vector2 lhs, const Vector2& rhs) { lhs -= rhs; return lhs; }

		/**
		* @brief  Add two Vector2 together. 
		* @param lhs Vector2 on the left side of the operator.
		* @param rhs Vector2 on the right side of the operator.
		* @return A Vector2 holding the sum of the addition
		*/
		friend Vector2 operator+(Vector2 lhs, const Vector2& rhs) { lhs += rhs; return lhs; }
		
		/**
		* @brief  Multiply two Vector2 together(x*x, y*y).
		* @param lhs Vector2 on the left side of the operator.
		* @param rhs Vector2 on the right side of the operator.
		* @return A Vector2 holding the sum of the multiplication
		*/
		friend Vector2 operator*(Vector2 lhs, const Vector2& rhs) { lhs *= rhs; return lhs; }
		
		/**
		* @brief  Divide two Vector2 together(x/x, y/y).
		* @param lhs Vector2 on the left side of the operator.
		* @param rhs Vector2 on the right side of the operator.
		* @return A Vector2 holding the sum of the multiplication
		*/
		friend Vector2 operator/(Vector2 lhs, const Vector2& rhs) { lhs /= rhs; return lhs; }

		/**
		* @brief Calculate the dot product of two vectors.
		*
		* @param rhs The first vector.
		* @return The dot product.
		*/
		[[nodiscard]] float Dot(const Vector2& rhs) const { return x * rhs.x + y * rhs.y; }

		/**
		* @brief Calculate the Magnitude.
		*
		* @return Magnitude of vector.
		*/
		[[nodiscard]] float Magnitude() const;

		/**
		* @brief This function is more Opti because no have Square.
		*
		* @return Square Magnitude.
		*/
		[[nodiscard]] float SquareMagnitude() const { return x * x + y * y; }

		/**
		* @brief Checks whether vector is normalized.
		*
		* @return true if normalized, false otherwise.
		*/
		[[nodiscard]] bool IsNormalize() const { float sqrtMagnitude = SquareMagnitude(); return 0.9999995f < sqrtMagnitude && sqrtMagnitude < 1.0000005f;}

		
		/** @brief Normalize a vector */
		void Normalize() { *this /= Magnitude(); }

		
		/**
		 * @brief Normalize a Vector 
		 * @return a normalize copy of the vector 
		 */
		[[nodiscard]] Vector2 GetNormalize() const { float size = Magnitude(); return Vector2(x / size, y / size); }

		/**
		* @brief Euclidean distance between two points.
		*
		* @param lhs The first point.
		* @param rhs The second point.
		* @return The distance between two points.
		*/
		[[nodiscard]] static float DistanceBetween(const Vector2& lhs, const Vector2& rhs) { return (lhs - rhs).Magnitude(); }

		/**
		* @brief Euclidean distance between two points.
		*
		* @param other The Other point.
		* @return The distance between two points.
		*/
		[[nodiscard]] float DistanceTo(const Vector2& other) const { return DistanceBetween(*this, other); }

		/**
		* @brief Extract angle between two vectors.
		*
		* @param lhs The first point.
		* @param rhs The second point.
		* @return A angle in Radian.
		*/
		[[nodiscard]] static Radian ExtractAngleBetween(Vector2 lhs, Vector2 rhs);

		/**
		* @brief Get angle between two Unit vectors.
		*
		* @param lhs The first point.
		* @param rhs The second point.
		* @return A angle in Radian.
		*/
		[[nodiscard]] static Radian GetAngleBetweenUnitVector(Vector2 const& lhs, Vector2 const& rhs) { return acos(lhs.Dot(rhs)); }

		float& operator[](int index)
		{
			return ((float*)this)[index];
		};

		float operator[](int index)const
		{
			return ((float*)this)[index];
		};
	};
}