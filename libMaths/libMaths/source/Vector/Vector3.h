#pragma once

#include "Core/Angle.h"
#include "Core/CMath.h"

namespace LibMath
{
	struct Vector4;

	/**
	* Vector3 is a mathematical structure combining 3 value in a single entity.
	* <p>
	* A Vector3 can be use as an abstract structure to manipulate a point, a
	* normal or a movement in a 3D environment. Those 3D structure can be
	* rotate and scale with a Matrix3. They can also be translate and scale
	* using arithmetic operation.
	* <p>
	* In a 3D Environment the x, y, z component represent exact coordinate for 
	* point, direction for normal or distance for movement.
	* 
	* @author		Francis Blanchet
	* @version		1.0
	* @see			Matrix4
	* @since		1.0
	*/
	struct Vector3
	{
		/**
		* Default constructor. All components are zeros.
		*/
		Vector3() = default;
		
		/**
		* Default copy constructor.
		*
		* @param other	Vector3 to copied
		*/
		Vector3(const Vector3& other) = default;
		
		/**
		* Default assignment operator.
		*
		* @param other	Vector3 to copied
		* @return		A reference to this Vector3
		*/
		Vector3& operator=(const Vector3& other) = default;
		
		/**
		* Default destructor.
		*/
		~Vector3() = default;

		/**
		* Constructor with a single value for all components
		*
		* @param value	float value for all component
		*/
		explicit Vector3(const float value) : x(value), y(value), z(value) {}
		
		/**
		* Constructor with a specific value for each components
		*
		* @param px		position of this Vector3 on the Left-Right Axis also known as the
		*				X-Axis
		* @param py		position of this Vector3 on the Up-Down Axis also known as the
		*				Y-Axis
		* @param pz		position of this Vector3 on the Forward-Backward Axis also known
		*				as the Z-Axis
		*/
		Vector3(const float px, const float py, const float pz) : x(px), y(py), z(pz) {}

		/**
		* Constructor converting a Vector4 into a Vector3. This constructor just drop the
		* w component of the base Vector4. If you are converting a point from a 3D
		* environment, you should make sure the base Vector4 is homogenize before doing
		* this conversion.
		* 
		* @param other	Vector4 use as a base to create this Vector3
		*/
		explicit Vector3(const Vector4& other);
		
		/**
		* Assignment operator converting a Vector4 into a Vector3. This constructor just
		* drop the w component of the base Vector4. If you are converting a point from a
		* 3D environment, you should make sure the base Vector4 is homogenize before doing
		* this conversion.
		*
		* @param other	Vector4 use as a base to create this Vector3
		* @return		A reference to this Vector3
		*/
		Vector3& operator=(const Vector4& other);

		/**
		* Array subscript operator that match the following index with the following
		* component [0 -> x], [1 -> y], [2 -> z]
		*
		* @param index	Component index to access
		* @return		Component at the given index
		*/
		/*@{*/
		[[nodiscard]] float& operator[](int index) { return ((float*)this)[index]; };
		[[nodiscard]] float operator[](int index) const { return ((float*)this)[index]; };
		/*@}*/

		/**
		* Create a Vector3 where all component are zeros. This is equivalent with a call
		* to the default constructor.
		*/
		static Vector3 const Zero;
		
		/**
		* Create a Vector3 where all component are ones. This is equivalent with a call
		* to Vector3(1.f).
		*/
		static Vector3 const One;
		
		/**
		* Create unit Vector3 representing the right direction.
		*/
		static Vector3 const Right;
		
		/**
		* Create unit Vector3 representing the left direction.
		*/
		static Vector3 const Left;
		
		/**
		* Create unit Vector3 representing the up direction.
		*/
		static Vector3 const Up;
		
		/**
		* Create unit Vector3 representing the down direction.
		*/
		static Vector3 const Down;
		
		/**
		* Create unit Vector3 representing the forward direction.
		*/
		static Vector3 const Front;
		
		/**
		* Create unit Vector3 representing the backward direction.
		*/
		static Vector3 const Back;

		/**
		* Compare this Vector3 with an other one
		*
		* @param other	Vector3 use as a comparison
		* @return		Whether or not both Vector3 have the exact same component values.
		*/
		[[nodiscard]] bool operator==(const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }
		
		/**
		* Compare this Vector3 with an other one
		*
		* @param other	Vector3 use as a comparison
		* @return		Whether or not at least one of the component have a different
		*				value in both Vector
		*/
		[[nodiscard]] bool operator!=(Vector3 const& other) const { return !(*this == other); }
		
		/**
		* Add an other Vector3 to this Vector3. This Vector3 component values will be
		* increased by the other Vector3 component values. Note that in 3D environment
		* adding two point together is a non-sense.
		*
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A reference on this Vector3
		*/
		/*@{*/
		friend Vector3& operator+=(Vector3& lhs, const Vector3& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; return lhs; }
		friend Vector3& operator+=(Vector3& lhs, float rhs) { lhs.x += rhs; lhs.y += rhs; lhs.z += rhs; return lhs; }
		/*@}*/
		
		/**
		* Subtract an other Vector3 from this Vector3. This Vector3 component values
		* will be decreased by the other Vector3 component values.
		*
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A reference on this Vector3
		*/
		/*@{*/
		friend Vector3& operator-=(Vector3& lhs, const Vector3& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; return lhs; }
		friend Vector3& operator-=(Vector3& lhs, float rhs) { lhs.x -= rhs; lhs.y -= rhs; lhs.z -= rhs; return lhs; }
		/*@}*/
		
		/**
		* Multiply an other Vector3 to this Vector3. This Vector3 component values will
		* be multiply by the other Vector3 component values.
		*
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A reference on this Vector3
		*/
		/*@{*/
		friend Vector3& operator*=(Vector3& lhs, const Vector3& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; return lhs; }
		friend Vector3& operator*=(Vector3& lhs, float rhs) { lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; return lhs; }
		/*@}*/
		
		/**
		* Divide an other Vector3 from this Vector3. This Vector3 component values will
		* be decreased by the other Vector3 component values.
		*
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A reference on this Vector3
		*/
		/*@{*/
		friend Vector3& operator/=(Vector3& lhs, const Vector3& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; return lhs; }
		friend Vector3& operator/=(Vector3& lhs, float rhs) { lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; return lhs; }
		/*@}*/

		/**
		* Add two Vector3 together. The resulting Vector3's component values will be the
		* sum of the component of both Vector3. Note that in 3D environment adding two
		* point together is a non-sense.
		*
		* @param lhs	Vector3 on the left side of the operator.
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A Vector3 holding the sum of the addition
		*/
		/*@{*/
		[[nodiscard]] friend Vector3 operator+(Vector3 lhs, const Vector3& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; return lhs; }
		[[nodiscard]] friend Vector3 operator+(Vector3 lhs, float rhs) { lhs.x += rhs; lhs.y += rhs; lhs.z += rhs; return lhs; }
		[[nodiscard]] friend Vector3 operator+(float lhs, Vector3 rhs) { rhs.x += lhs; rhs.y += lhs; rhs.z += lhs; return rhs; }
		/*@}*/
		
		/**
		* Create an inverse copy of this Vector3. The resulting Vector3's component values will
		* be the inverse values of the component of this Vector3.
		*
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A Vector3 holding the Inverse
		*/
		[[nodiscard]] friend Vector3 operator-(const Vector3& rhs) { return Vector3(-rhs.x, -rhs.y, -rhs.z); }
		/**
		* Subtract a Vector3 from an other. The resulting Vector3's component values
		* will be the difference of the component of both Vector3.
		*
		* @param lhs	Vector3 on the left side of the operator.
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A Vector3 holding the difference of the subtraction
		*/
		/*@{*/
		[[nodiscard]] friend Vector3 operator-(Vector3 lhs, const Vector3& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; return lhs; }
		[[nodiscard]] friend Vector3 operator-(Vector3 lhs, float rhs) { lhs.x -= rhs; lhs.y -= rhs; lhs.z -= rhs; return lhs; }
		[[nodiscard]] friend Vector3 operator-(float lhs, Vector3 rhs) { rhs.x = lhs - rhs.x; rhs.y = lhs - rhs.y; rhs.z = lhs - rhs.z; return rhs; }
		/*@}*/
		
		/**
		* Multiply two Vector3 together. The resulting Vector3's component values will
		* be the product of the component of both Vector3.
		*
		* @param lhs	Vector3 on the left side of the operator.
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A Vector3 holding the product of the multiplication
		*/
		/*@{*/
		[[nodiscard]] friend Vector3 operator*(Vector3 lhs, const Vector3& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; return lhs; }
		[[nodiscard]] friend Vector3 operator*(Vector3 lhs, float rhs) { lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; return lhs; }
		[[nodiscard]] friend Vector3 operator*(float lhs, Vector3 rhs) { rhs.x *= lhs; rhs.y *= lhs; rhs.z *= lhs; return rhs; }
		/*@}*/
		
		/**
		* Divide a Vector3 by an other. The resulting Vector3's component values will be
		* the quotient of the component of both Vector3.
		*
		* @param lhs	Vector3 on the left side of the operator.
		* @param rhs	Vector3 on the right side of the operator.
		* @return		A Vector3 holding the difference of the subtraction
		*/
		/*@{*/
		[[nodiscard]] friend Vector3 operator/(Vector3 lhs, const Vector3& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; return lhs; }
		[[nodiscard]] friend Vector3 operator/(Vector3 lhs, float rhs) { lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; return lhs; }
		[[nodiscard]] friend Vector3 operator/(float lhs, Vector3 rhs) { rhs.x = lhs / rhs.x; rhs.y = lhs / rhs.y; rhs.z = lhs / rhs.z; return rhs; }
		/*@}*/

		/**
		* Calculate the cross product between this Vector3 and an other one
		*
		* @param other	Vector3 use to do the cross product.
		* @return		A Vector3 holding the product result of the cross product between
		*				the two Vector3
		*/
		/*@{*/
		[[nodiscard]] Vector3 Cross(const Vector3& other) const { return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
		[[nodiscard]] static Vector3 Cross(const Vector3& lhs, const Vector3& rhs) { return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x); }
		/*@}*/

		/**
		* Calculate the dot product between this Vector3 and an other one
		*
		* @param other	Vector3 use to do the dot product.
		* @return		the result of the dot product between the two Vector3
		*/
		/*@{*/
		[[nodiscard]] float Dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }
		[[nodiscard]] static float Dot(const Vector3& lhs, const Vector3& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
		/*@}*/

		/**
		* Assuming this Vector3 is not a point, calculate the magnitude of this Vector3.
		* Or in other word Calculate how long would this Vector3 be if drawn in a volume.
		*
		* @return		Vector length / magnitude
		* @see			SquareMagnitude()
		*/
		/*@{*/
		[[nodiscard]] float Magnitude() const;
		[[nodiscard]] static float Magnitude(const Vector3& vector) { return vector.Magnitude(); }
		/*@}*/
		/**
		* Assuming this Vector3 is not a point, calculate the square magnitude of this
		* Vector3. This is useful if all you are trying to do is compare two vector as it
		* as a lesser computation cost than it more exact counter part
		*
		* @return		Vector length / magnitude but square
		* @see			Magnitude()
		*/
		/*@{*/
		[[nodiscard]] float SquareMagnitude() const { return x * x + y * y + z * z; }
		[[nodiscard]] static float SquareMagnitude(const Vector3& vector) { return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z; }
		/*@}*/

		/**
		* Compare this Vector3 magnitude with the magnitude an other one
		*
		* @param other	Vector3 use as a comparaison
		* @return		Wheter or not this vector is shorter than the other
		*/
		[[nodiscard]] bool IsShorterThan(Vector3 const& other) const { return SquareMagnitude() < other.SquareMagnitude(); }
		/**
		* Compare this Vector3 magnitude with the magnitude an other one
		*
		* @param other	Vector3 use as a comparaison
		* @return		Wheter or not this vector is shorter or as long as the other
		*/
		[[nodiscard]] bool IsShorterOrEqualTo(Vector3 const& other) const { return SquareMagnitude() <= other.SquareMagnitude(); }
		/**
		* Compare this Vector3 magnitude with the magnitude an other one
		*
		* @param other	Vector3 use as a comparaison
		* @return		Wheter or not this vector is longer than the other
		*/
		[[nodiscard]] bool IsLongerThan(Vector3 const& other) const { return SquareMagnitude() > other.SquareMagnitude(); }
		/**
		* Compare this Vector3 magnitude with the magnitude an other one
		*
		* @param other	Vector3 use as a comparaison
		* @return		Wheter or not this vector is longer or as long as the other
		*/
		[[nodiscard]] bool IsLongerOrEqualTo(Vector3 const& other) const { return SquareMagnitude() >= other.SquareMagnitude(); }
		
		/**
		* Assuming this Vector3 is not a point, determine if this Vector3 is a unit
		* vector or not (magnitude == 1.f).
		*
		* @param precision	Maximum deviation from 1.f this Vector3 magnitude can be and
		*					still assume that it is a unit vector
		* @return			Whether or not this Vector3 is a unit vector
		*/
		[[nodiscard]] bool IsNormalize(float precision = .0000005f) const { const  float magnitude = SquareMagnitude();  return 1.f - precision < magnitude && magnitude < 1.f + precision; }
		/**
		* Assuming this Vector3 is not a point, change this Vector3 into proportional
		* unit vector version of itself.
		*/
		Vector3& Normalize() { *this /= Magnitude(); return *this; }
		/**
		* Assuming this Vector3 is not a point, create a unit Vector3 proportional to
		* this Vector3.
		* 
		* @return		A unit Vector3
		*/
		/*@{*/
		[[nodiscard]] Vector3 GetNormalize() const { const float size = Magnitude(); return Vector3(x / size, y / size, z / size); }
		[[nodiscard]] static Vector3 Normalize(Vector3 vector) { const float size = vector.Magnitude(); vector.x /= size; vector.y /= size; vector.z /= size; return vector; }
		/*@}*/

		/**
		* Assuming both this Vector3 and the other are point, calculate the distance
		* between those two points
		*
		* @param other	Vector3 representing a point.
		* @return		the distance between the two points
		*/
		[[nodiscard]] float DistanceTo(const Vector3& other) const { return DistanceBetween(*this, other); }
		/**
		* Assuming both Vector3 are point, calculate the distance between those two
		* points
		*
		* @param first	Vector3 representing a point.
		* @param second	Vector3 representing a point.
		* @return		the distance between the two points
		*/
		[[nodiscard]] static float DistanceBetween(const Vector3& first, const Vector3& second) { return (first - second).Magnitude(); }
		
		/**
		* Assuming both this Vector3 and the other are not point, calculate the angle
		* between those two Vector3
		*
		* @param other	Vector3 representing a direction.
		* @return		the shortest angle between the vector.
		*/
		[[nodiscard]] Radian AngleTo(const Vector3& other) { return AngleBetween(*this, other); }
		
		/**
		* Assuming both Vector3 are not point, calculate the angle between those two
		* Vector3
		*
		* @param first	Vector3 representing a direction.
		* @param second	Vector3 representing a direction.
		* @return		the shortest angle between the vector.
		*/
		[[nodiscard]] static Radian AngleBetween(Vector3 first, Vector3 second);
		
		/**
		* Assuming both this Vector3 and the other are not point, calculate the angle
		* between those two Vector3 ignoring the y component of both Vector3.
		*
		* @param other	Vector3 representing a direction.
		* @return		the oriented angle between the vector looking from the sky.
		*/
		[[nodiscard]] Radian TopDownAngleTo(const Vector3& other) { return TopDownAngleBetween(*this, other); }
		
		/**
		* Assuming both Vector3 are not point, calculate the angle between those two
		* Vector3 ignoring the y component of both Vector3.
		*
		* @param first	Vector3 representing a direction.
		* @param second	Vector3 representing a direction.
		* @return		the oriented angle between the vector looking from the sky.
		*/
		[[nodiscard]] static Radian TopDownAngleBetween(Vector3 first, Vector3 second);
		
		/**
		* Assuming both Vector3 are normalize, calculate the angle between those two
		* Vector3
		*
		* @param first	unit Vector3 representing a direction.
		* @param second	unit Vector3 representing a direction.
		* @return		the shortest angle between the vector.
		*/
		[[nodiscard]] static Radian GetAngleBetweenUnitVector(const Vector3& first, Vector3 const& second) { return acos(first.Dot(second)); }
		
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;


		/*todo: test*/[[nodiscard]] static Vector3 Lerp(Vector3 const& lhs, Vector3 const& rhs, float alpha) { return Vector3((1 - alpha) * lhs.x + alpha * rhs.x, (1 - alpha) * lhs.y + alpha * rhs.y, (1 - alpha) * lhs.z + alpha * rhs.z); }

		// todo: glm reflect
		// todo: glm refract
	};

	inline Vector3 const Vector3::Zero = Vector3(0.f, 0.f, 0.f);
	inline Vector3 const Vector3::One = Vector3(1.f, 1.f, 1.f);
	inline Vector3 const Vector3::Right = Vector3(1.f, 0.f, 0.f);
	inline Vector3 const Vector3::Left = Vector3(-1.f, 0.f, 0.f);
	inline Vector3 const Vector3::Up = Vector3(0.f, 1.f, 0.f);
	inline Vector3 const Vector3::Down = Vector3(0.f, -1.f, 0.f);
	inline Vector3 const Vector3::Front = Vector3(0.f, 0.f, 1.f);
	inline Vector3 const Vector3::Back = Vector3(0.f, 0.f, -1.f);
}