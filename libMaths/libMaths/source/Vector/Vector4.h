#pragma once

namespace LibMath
{
	struct Vector3;

	/**
	* Vector4 is a mathematical structure combining 4 value in a single entity.
	* <p>
	* A Vector4 can be use as an abstract structure to manipulate a point or a
	* direction  in a 3D environment. Those 3D structure can be translate, rotate,
	* scale and apply a projection transformation with a Matrix4.
	* <p>
	* In a 3D Environment the x, y, z component represent either a position or a
	* direction vector. The w component is the homogeneous value and represent
	* whether this Vector4 is a direction (w == 0.f) or a point (w != 0.f). Note
	* that if the homogeneous is not equal to 1.f and not equal to 0.f the
	* position is not in the normal 3D space (3D space as human understand it)
	* and must be Homogenize before being use.
	*
	* @author		Francis Blanchet
	* @version		1.0
	* @see			Matrix4
	* @see			Vector3
	* @since		1.0
	*/
	struct Vector4
	{
		/**
		* Default constructor. All components are zeros.
		*/
		Vector4() = default;

		/**
		* Default copy constructor.
		*
		* @param other	Vector4 to copied
		*/
		Vector4(const Vector4& other) = default;

		/**
		* Default assignment operator.
		*
		* @param other	Vector4 to copied
		* @return		A reference to this Vector4
		*/
		Vector4& operator=(const Vector4& other) = default;
		/**
		* Default destructor.
		*/
		~Vector4() = default;

		/**
		* Constructor with a single value for all compponents
		*
		* @param value	float value for all component
		*/
		Vector4(const float value) : x(value), y(value), z(value), w(value) {}

		/**
		* Constructor with a specific value for each compponents
		*
		* @param px		position of this Vector4 on the Left-Right Axis also known as the
		*				X-Axis
		* @param py		position of this Vector4 on the Up-Down Axis also known as the
		*				Y-Axis
		* @param pz		position of this Vector4 on the Forward-Backward Axis also known
		*				as the Z-Axis
		* @param pw		homogeneous component of this vector
		*/
		Vector4(const float px, const float py, const float pz, const float pw) : x(px), y(py), z(pz), w(pw) {}

		/**
		* Array subscript operator that match the following index with the following
		* component [0 -> x], [1 -> y], [2 -> z], [3 -> w]
		*
		* @param index	Component index to access
		* @return		Component at the given index
		*/
		/*@{*/
		[[nodiscard]] float& operator[](int index) { return ((float*)this)[index]; };
		[[nodiscard]] float operator[](int index) const { return ((float*)this)[index]; };
		/*@}*/

		/**
		* Create a Vector4 representing a direction (w == 0.f)
		*
		* @param px		position of this Vector4 on the Left-Right Axis also known as the
		*				X-Axis
		* @param py		position of this Vector4 on the Up-Down Axis also known as the
		*				Y-Axis
		* @param pz		position of this Vector4 on the Forward-Backward Axis also known
		*				as the Z-Axis
		* @return		A Vector4 with w == 0.f
		*/
		static Vector4 Direction(const float px, const float py, const float pz) { return Vector4(px, py, pz, 0.f); }
		/**
		* Create a Vector4 representing a direction from a Vector3 base (w == 0.f)
		*
		* @param other	Vector3 use as a base to create this Vector4
		* @return		A Vector4 with w == 0.f
		*/
		static Vector4 Direction(const Vector3& other);

		/**
		* Create a Vector4 representing a point (w == 1.f)
		*
		* @param x		position of this Vector4 on the Left-Right Axis also known as the
		*				X-Axis
		* @param y		position of this Vector4 on the Up-Down Axis also known as the
		*				Y-Axis
		* @param z		position of this Vector4 on the Forward-Backward Axis also known
		*				as the Z-Axis
		* @return		A Vector4 with w == 1.f
		*/
		static Vector4 Point(const float x, const float y, const float z) { return Vector4(x, y, z, 1.f); }

		/**
		* Create a Vector4 representing a point from a Vector3 base (w == 1.f)
		*
		* @param other	Vector3 use as a base to create this Vector4
		* @return		A Vector4 with w == 1.f
		*/
		static Vector4 Point(const Vector3& other);

		/**
		* Compare this Vector4 with an other one
		*
		* @param other	Vector4 use as a comparaison
		* @return		Whether or not both Vector4 have the exact same component values.
		*/
		bool operator==(const Vector4& other) const { return w == other.w && x == other.x && y == other.y && z == other.z; }
		/**
		* Compare this Vector4 with an other one
		*
		* @param other	Vector4 use as a comparaison
		* @return		Wheter or not at least one of the component have a different
		*				value in both Vector
		*/
		bool operator!=(const Vector4& other) const { return w != other.w || x != other.x || y != other.y || z != other.z; }

		/**
		* Add an other Vector4 to this Vector4. This Vector4 component values will be
		* increased by the other Vector4 component values. Note that in 3D environment
		* adding two point together is a non-sense.
		*
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A reference on this Vector4
		*/
		Vector4& operator+=(const Vector4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
		/**
		* Substract an other Vector4 from this Vector4. This Vector4 component values
		* will be decreased by the other Vector4 component values.
		*
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A reference on this Vector4
		*/
		Vector4& operator-=(const Vector4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
		/**
		* Multiply an other Vector4 to this Vector4. This Vector4 component values will
		* be multiply by the other Vector4 component values.
		*
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A reference on this Vector4
		*/
		Vector4& operator*=(const Vector4& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this; }
		/**
		* Divide an other Vector4 from this Vector4. This Vector4 component values will
		* be decreased by the other Vector4 component values.
		*
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A reference on this Vector4
		*/
		Vector4& operator/=(const Vector4& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w; return *this; }

		/**
		* Add two Vector4 together. The resulting Vector4's component values will be the
		* sum of the component of both Vector4. Note that in 3D environment adding two
		* point together is a non-sense.
		*
		* @param lhs	Vector4 on the left side of the operator.
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A Vector4 holding the sum of the addition
		*/
		friend Vector4 operator+(Vector4 lhs, const Vector4& rhs) { lhs += rhs; return lhs; }
		/**
		* Create an inverse copy of this Vector4. The resulting Vector4's component values will
		* be the inveres values of the component of this Vector4.
		*
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A Vector4 holding the Inverse
		*/
		friend Vector4 operator-(const Vector4& rhs) { return Vector4(-rhs.x, -rhs.y, -rhs.z, -rhs.w); }
		/**
		* Substract a Vector4 from an other. The resulting Vector4's component values
		* will be the difference of the component of both Vector4.
		*
		* @param lhs	Vector4 on the left side of the operator.
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A Vector4 holding the difference of the substraction
		*/
		friend Vector4 operator-(Vector4 lhs, const Vector4& rhs) { lhs -= rhs; return lhs; }
		/**
		* Multiply two Vector4 together. The resulting Vector4's component values will
		* be the product of the component of both Vector4.
		*
		* @param lhs	Vector4 on the left side of the operator.
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A Vector4 holding the product of the multiplication
		*/
		friend Vector4 operator*(Vector4 lhs, const Vector4& rhs) { lhs *= rhs; return lhs; }
		/**
		* Divide a Vector4 by an other. The resulting Vector4's component values will be
		* the quotient of the component of both Vector4.
		*
		* @param lhs	Vector4 on the left side of the operator.
		* @param rhs	Vector4 on the right side of the operator.
		* @return		A Vector4 holding the difference of the substraction
		*/
		friend Vector4 operator/(Vector4 lhs, const Vector4& rhs) { lhs /= rhs; return lhs; }

		/**
		* Assuming this Vector4 is in 3D space, determine if this Vector4 is a direction
		* or not.
		*
		* @return		Whether or not this Vector4 represent a direction in a 3D
		*				environment
		*/
		[[nodiscard]] bool IsDirection() const { return w == 0.f; }
		/**
		* Assuming this Vector4 is in 3D space, determine if this Vector4 is a point or
		* not.
		*
		* @return		Whether or not this Vector4 represent a point in a 3D environment
		*/
		[[nodiscard]] bool IsPoint() const { return w != 0.f; }

		/**
		* Calculate de dot product between this Vector4 and an other one
		*
		* @param other	Vector4 use to do the dot product.
		* @return		the result of the dot product between the two Vector4
		*/
		[[nodiscard]] float Dot(Vector4 const& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

		/**
		* Assuming this Vector4 is in 3D space and represent a point, determine if this
		* Vector4 is in normal space coordinate or not (w == 1.f).
		*
		* @return		Whether or not this Vector4 represent a point in a 3D environment
		*/
		bool IsHomogenize() const { return w == 1.f; }
		/**
		* Assuming this Vector4 is in 3D space and represent a point, Change this Vector4
		* to bring it in normal space coordinate.
		*/
		void Homogenize() { x /= w; y /= w; z /= w; w = 1.f; }
		/**
		* Assuming this Vector4 is in 3D space and represent a point, create a copy of
		* this Vector4 in normal space coordinate.
		*
		* @return		A Vector4 representing the same point as this one but in normal
		*				space coordinate.
		*/
		[[nodiscard]] Vector4 GetHomogenize() const { return Vector4(x / w, y / w, z / w, 1.f); }

		/*
		* @name Coordinates
		*/
		/*@{*/
		float x = 0.f;/**< Left - Right Axis value (X - Axis)*/
		float y = 0.f;/**< Up - Down Axis value (Y - Axis)*/
		float z = 0.f;/**< Forward - Backward Axis value (Z - Axis)*/
		/*@}*/

		/*
		* @name space Coordinates
		*/
		/*@{*/
		float w = 0.f;/**< homogeneous component*/
		/*@}*/
	};
}