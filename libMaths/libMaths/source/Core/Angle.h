#pragma once

#include "AngleDefine.h"

namespace LibMath
{
	enum class RotationOrder : char
	{
		Xfirst = 1,
		Yfirst = 2,
		Zfirst = 0,
		Xsecond = 4,
		Ysecond = 8,
		Zsecond = 0,
		Xlast = 16,
		Ylast = 32,
		Zlast = 0,
	};

	enum class RotationSequence : char
	{
		XYX = (char)RotationOrder::Xfirst + (char)RotationOrder::Ysecond + (char)RotationOrder::Xlast,
		XYZ = (char)RotationOrder::Xfirst + (char)RotationOrder::Ysecond + (char)RotationOrder::Zlast,
		XZX = (char)RotationOrder::Xfirst + (char)RotationOrder::Zsecond + (char)RotationOrder::Xlast,
		XZY = (char)RotationOrder::Xfirst + (char)RotationOrder::Zsecond + (char)RotationOrder::Ylast,

		YXY = (char)RotationOrder::Yfirst + (char)RotationOrder::Xsecond + (char)RotationOrder::Ylast,
		YXZ = (char)RotationOrder::Yfirst + (char)RotationOrder::Xsecond + (char)RotationOrder::Zlast,
		YZX = (char)RotationOrder::Yfirst + (char)RotationOrder::Zsecond + (char)RotationOrder::Xlast,
		YZY = (char)RotationOrder::Yfirst + (char)RotationOrder::Zsecond + (char)RotationOrder::Ylast,

		ZXY = (char)RotationOrder::Zfirst + (char)RotationOrder::Xsecond + (char)RotationOrder::Ylast,
		ZXZ = (char)RotationOrder::Zfirst + (char)RotationOrder::Xsecond + (char)RotationOrder::Zlast,
		ZYX = (char)RotationOrder::Zfirst + (char)RotationOrder::Ysecond + (char)RotationOrder::Xlast,
		ZYZ = (char)RotationOrder::Zfirst + (char)RotationOrder::Ysecond + (char)RotationOrder::Zlast,
	};

	/**
	 * @brief Virtual struct for Degree and Radian.
	 */
	struct Angle
	{
		/**
		 * @brief Default constructor.
		 */
		Angle() = default;
		/**
		 * @brief Constructor with value.
		 * @param data Value of the angle.
		 */
		Angle(float data) : data(data) {}

		/**
		 * @brief Virtual function to clamp the value of the angle.
		 */
		virtual void Clamp() = 0;

		/**
		 * @brief Virtual function returning a copy of the angle value in degree clamped.
		 * @return Angle clamped in degree.
		 */
		virtual float clampDeg() const = 0;
		/**
		 * @brief Virtual function returning a copy of the angle value in radian clamped.
		 * @return Angle clamped in radian.
		 */
		virtual float clampRad() const = 0;
		
		/**
		 * @brief Virtual function returning the angle value in degree.
		 * @return Angle in degree.
		 */
		virtual float deg() const = 0;
		/**
		 * @brief Virtual function returning the angle value in radian.
		 * @return Angle in radian.
		 */
		virtual float rad() const = 0;

		/**
		 * @brief Value of the angle.
		 */
		float data = 0.f;
	};

	/**
	 * @brief Forward declaration of Radian for Degree.
	 */
	struct Radian;

	/**
	 * @brief Struct Degree overriding Angle.
	 */
	struct Degree : public Angle
	{
		/**
		 * @brief Default constructor.
		 */
		Degree() = default;

		/**
		 * @brief Constructor with value.
		 * @param data Value of the angle.
		 */
		explicit Degree(float data) : Angle(data) {}

		/**
		 * @brief Constructor by reference of an other degree.
		 * @param other The degree being copied.
		 */
		Degree(Degree const& other) = default;

		/**
		 * @brief Constructor by conversion of a radian.
		 * @param other The Radian being converted.
		 */
		Degree(Radian const& other);

		//------------------

		/**
		 * @brief Set the degree value with another one.
		 * @param other The degree that will be used.
		 * @return A reference to the degree.
		 */
		Degree& operator=(const Degree& other) = default;

		/**
		 * @brief Test if two degrees are equal.
		 * @param other The degree that will be compared.
		 * @return True if they are the same.
		 */
		bool operator==(Degree other) const { return data == other.data; }
		/**
		 * @brief Test if a degree is equal with a radian.
		 * @param other The radian that will be compared.
		 * @return True if they are the same.
		 */
		bool operator==(Radian other) const;
		/**
		 * @brief Test if two degrees are not equal.
		 * @param other The degree that will be compared.
		 * @return True if they are not the same.
		 */
		bool operator!=(Degree other) const { return data != other.data; };
		/**
		 * @brief Test if a degree is not equal with a radian.
		 * @param other The radian that will be compared.
		 * @return True if they are not the same.
		 */
		bool operator!=(Radian other) const;

		/**
		 * @brief Test if a degree is less than another one.
		 * @param other The degree that will be compared.
		 * @return True if its left-hand operand is less than its right-hand operand.
		 */
		bool operator<(Degree other) const { return data < other.data; }
		/**
		 * @brief Test if a degree is greater than another one.
		 * @param other The degree that will be compared.
		 * @return True if its left-hand operand is greater than its right-hand operand.
		 */
		bool operator>(Degree other) const { return data > other.data; }
		/**
		 * @brief Test if a degree is less than or equal to another one.
		 * @param other The degree that will be compared.
		 * @return True if its left-hand operand is less than or equal to its right-hand operand.
		 */
		bool operator<=(Degree other) const { return data <= other.data; }
		/**
		 * @brief Test if a degree is greater than or equal to another one.
		 * @param other The degree that will be compared.
		 * @return True if its left-hand operand is greater than or equal to its right-hand operand.
		 */
		bool operator>=(Degree other) const { return data >= other.data; }

		/**
		 * @brief Increase the value of a degree by another degree.
		 * @param Degree that will be added to the degree.
		 * @return A reference to the degree.
		 */
		Degree& operator+=(Degree rhs) { data += rhs.data; return *this; }
		/**
		 * @brief Decrease the value of a degree by another degree.
		 * @param Degree that will be subtracted to the degree.
		 * @return A reference to the degree.
		 */
		Degree& operator-=(Degree rhs) { data -= rhs.data; return *this; }
		/**
		 * @brief Multiply the value of a degree by a float.
		 * @param Float value that will be multiplied to the degree.
		 * @return A reference to the degree.
		 */
		Degree& operator*=(float rhs) { data *= rhs; return *this; }
		/**
		 * @brief Divide the value of a degree by a float.
		 * @param Float value that will be divided to the degree.
		 * @return A reference to the degree.
		 */
		Degree& operator/=(float rhs) { data /= rhs; return *this; }

		/**
		 * @brief Add two degrees.
		 * @param lhs First degree that will be added to the second.
		 * @param rhs Second degree that will be added to the first.
		 * @return New degree with the value of the 2 parameters added.
		 */
		friend Degree operator+(Degree lhs, Degree rhs) { lhs += rhs; return lhs; }
		/**
		 * @brief Subtract one degree to another one.
		 * @param lhs First degree that will be subtracted by the second.
		 * @param rhs Second degree that we want to subtracted from the first.
		 * @return New degree with the value of the first parameter subtracted by the second parameter.
		 */
		friend Degree operator-(Degree lhs, Degree rhs) { lhs -= rhs; return lhs; }
		/**
		 * @brief Multiply a degree by a float.
		 * @param lhs Degree that we will be multiplied to the float value.
		 * @param rhs Float value that will be multiplied to the degree.
		 * @return New degree with the value of the first parameter multiplied by the second parameter.
		 */
		friend Degree operator*(Degree lhs, float rhs) { lhs *= rhs; return lhs; }
		/**
		 * @brief Multiply a float by a degree.
		 * @param lhs Float value that will be multiplied to the degree.
		 * @param rhs Degree that we will be multiplied to the float value.
		 * @return New degree with the value of the first parameter multiplied by the second parameter.
		 */
		friend Degree operator*(float lhs, Degree rhs) { rhs *= lhs; return rhs; }
		/**
		 * @brief Divide a degree by a float.
		 * @param lhs Float value that will be used to divide the degree.
		 * @param rhs Degree that we will be divided by the float value.
		 * @return New degree with the value of the first parameter divided by the second parameter.
		 */
		friend Degree operator/(Degree lhs, float rhs) { lhs /= rhs; return lhs; }

		//------------------

		/**
		 * @brief Override function to clamp the value of the angle.
		 */
		void Clamp() override;

		/**
		 * @brief Override function returning a copy of the angle value in degree clamped.
		 * @return Float of the angle clamped in degree.
		 */
		float clampDeg() const override { Degree copy = *this; copy.Clamp(); return copy.deg(); }
		/**
		 * @brief Override function returning a copy of the angle value in radian clamped.
		 * @return Float of the angle clamped in radian.
		 */
		float clampRad() const override { Degree copy = *this; copy.Clamp(); return copy.rad(); }
		
		/**
		 * @brief Override function returning the angle value in degree.
		 * @return Float of the angle in degree.
		 */
		float deg() const override { return data; }
		/**
		 * @brief Override function returning the angle value in radian.
		 * @return Float of the angle in radian.
		 */
		float rad() const override { return DEGREE_TO_RADIAN(data); }
	};


	/**
	 * @brief Struct Radian overriding Angle.
	 */
	struct Radian : public Angle
	{
		/**
		 * @brief Default constructor.
		 */
		Radian() = default;

		/**
		 * @brief Constructor with value.
		 * @param data Value of the angle.
		 */
		explicit Radian(float data) : Angle(data) {}

		/**
		 * @brief Constructor by reference of an other Radian.
		 * @param other The degree being copied.
		 */
		Radian(Radian const& other) = default;

		/**
		 * @brief Constructor by conversion of a degree.
		 * @param other The degree being converted.
		 */
		Radian(Degree const& other) : Angle(DEGREE_TO_RADIAN(other.data)) {}

		//------------------

		/**
		 * @brief Set the degree value with another one.
		 * @param other The degree that will be used.
		 * @return A reference to the degree.
		 */
		Radian& operator=(const Radian& other) = default;

		/**
		 * @brief Test if two degrees are equal.
		 * @param other The degree that will be compared.
		 * @return True if they are the same.
		 */
		bool operator==(Radian other) const { return data == other.data; }
		/**
		 * @brief Test if a radian is equal with a degree.
		 * @param other The degree that will be compared.
		 * @return True if they are the same.
		 */
		bool operator==(Degree other) const;
		/**
		 * @brief Test if two radians are not equal.
		 * @param other The radian that will be compared.
		 * @return True if they are not the same.
		 */
		bool operator!=(Radian other) const { return data != other.data; }
		/**
		 * @brief Test if a radian is not equal with a degree.
		 * @param other The degree that will be compared.
		 * @return True if they are not the same.
		 */
		bool operator!=(Degree other) const;

		/**
		 * @brief Test if a radian is less than another one.
		 * @param other The radian that will be compared.
		 * @return True if its left-hand operand is less than its right-hand operand.
		 */
		bool operator<(Radian other) const { return data < other.data; }
		/**
		 * @brief Test if a radian is greater than another one.
		 * @param other The radian that will be compared.
		 * @return True if its left-hand operand is greater than its right-hand operand.
		 */
		bool operator>(Radian other) const { return data > other.data; }
		/**
		 * @brief Test if a radian is less than or equal to another one.
		 * @param other The radian that will be compared.
		 * @return True if its left-hand operand is less than or equal to its right-hand operand.
		 */
		bool operator<=(Radian other) const;
		/**
		 * @brief Test if a radian is greater than or equal to another one.
		 * @param other The radian that will be compared.
		 * @return True if its left-hand operand is greater than or equal to its right-hand operand.
		 */
		bool operator>=(Radian other) const;

		/**
		 * @brief Increase the value of a radian by another radian.
		 * @param Radian that will be added to the radian.
		 * @return A reference to the radian.
		 */
		Radian& operator+=(Radian rhs) { data += rhs.data; return *this; }
		/**
		 * @brief Decrease the value of a radian by another radian.
		 * @param Radian that will be subtracted to the radian.
		 * @return A reference to the radian.
		 */
		Radian& operator-=(Radian rhs) { data -= rhs.data; return *this; }
		/**
		 * @brief Multiply the value of a radian by a float.
		 * @param Radian value that will be multiplied to the radian.
		 * @return A reference to the radian.
		 */
		Radian& operator*=(float rhs) { data *= rhs; return *this; }
		/**
		 * @brief Divide the value of a radian by a float.
		 * @param Radian value that will be divided to the radian.
		 * @return A reference to the radian.
		 */
		Radian& operator/=(float rhs) { data /= rhs; return *this; }

		/**
		 * @brief Add two radians.
		 * @param lhs First radian that will be added to the second.
		 * @param rhs Second radian that will be added to the first.
		 * @return New radian with the value of the 2 parameters added.
		 */
		friend Radian operator+(Radian lhs, Radian rhs) { lhs += rhs; return lhs; }
		/**
		 * @brief Subtract one radian to another one.
		 * @param lhs First radian that will be subtracted by the second.
		 * @param rhs Second radian that we want to subtracted from the first.
		 * @return New radian with the value of the first parameter subtracted by the second parameter.
		 */
		friend Radian operator-(Radian lhs, Radian rhs) { lhs -= rhs; return lhs; }
		/**
		 * @brief Multiply a radian by a float.
		 * @param lhs Degree that we will be multiplied to the float value.
		 * @param rhs Radian value that will be multiplied to the degree.
		 * @return New radian with the value of the first parameter multiplied by the second parameter.
		 */
		friend Radian operator*(Radian lhs, float rhs) { lhs *= rhs; return lhs; }
		/**
		 * @brief Multiply a float by one radian.
		 * @param lhs Radian that we will be multiplied to the float value.
		 * @param rhs Float value that will be multiplied to the degree.
		 * @return New radian with the value of the first parameter multiplied by the second parameter.
		 */
		friend Radian operator*(float lhs, Radian rhs) { rhs *= lhs; return rhs; }
		/**
		 * @brief Divide a radian by a float.
		 * @param lhs Float value that will be used to divide the radian.
		 * @param rhs Radian that we will be divided by the float value.
		 * @return New radian with the value of the first parameter divided by the second parameter.
		 */
		friend Radian operator/(Radian lhs, float rhs) { lhs /= rhs; return lhs; }

		//------------------

		/**
		 * @brief Override function to clamp the value of the angle.
		 */
		void Clamp() override;

		/**
		 * @brief Override function returning a copy of the angle value in degree clamped.
		 * @return Float of the angle clamped in degree.
		 */
		float clampDeg() const override { Radian copy = *this; copy.Clamp(); return copy.deg(); }
		/**
		 * @brief Override function returning a copy of the angle value in radian clamped.
		 * @return Float of the angle clamped in radian.
		 */
		float clampRad() const override { Radian copy = *this; copy.Clamp(); return copy.rad(); }
		
		/**
		 * @brief Override function returning the angle value in radian.
		 * @return Float of the angle in radian.
		 */
		float rad() const override { return data; }
		/**
		 * @brief Override function returning the angle value in degree.
		 * @return Float of the angle in degree.
		 */
		float deg() const override { return RADIAN_TO_DEGREE(data); }
	};
	
	/**
	 * @brief Convert a radian in degree.
	 * @param other 
	 */
	inline Degree::Degree(Radian const& other) : Angle(RADIAN_TO_DEGREE(other.data)) {}

	/**
	 * @brief Compute the cos of an angle.
	 * @param angle The angle that will be computed.
	 * @return Value of cos.
	 */
	float cos(Angle const& angle);
	/**
	 * @brief Compute the cos of a degree.
	 * @param angle The degree that will be computed.
	 * @return Value of cos.
	 */
	float cos(Degree angle);
	/**
	 * @brief Compute the cos of a radian.
	 * @param angle The radian that will be computed.
	 * @return Value of cos.
	 */
	float cos(Radian angle);

	/**
	 * @brief Compute the sin of an angle.
	 * @param angle The angle that will be computed.
	 * @return Value of sin.
	 */
	float sin(Angle const& angle);
	/**
	 * @brief Compute the sin of a degree.
	 * @param angle The degree that will be computed.
	 * @return Value of sin.
	 */
	float sin(Degree angle);
	/**
	 * @brief Compute the sin of a radian.
	 * @param angle The radian that will be computed.
	 * @return Value of sin.
	 */
	float sin(Radian angle);

	/**
	 * @brief Compute the tan of an angle.
	 * @param angle The angle that will be computed.
	 * @return Value of tan.
	 */
	float tan(Angle const& angle);
	/**
	 * @brief Compute the tan of a degree.
	 * @param angle The degree that will be computed.
	 * @return Value of tan.
	 */
	float tan(Degree angle);
	/**
	 * @brief Compute the tan of a radian.
	 * @param angle The radian that will be computed.
	 * @return Value of tan.
	 */
	float tan(Radian angle);

	/**
	 * @brief Compute the acos of a float.
	 * @param x The value that will be computed.
	 * @return A new radian with the value computed by acos.
	 */
	Radian acos(float x);
	/**
	 * @brief Compute the asin of a float.
	 * @param x The value that will be computed.
	 * @return A new radian with the value computed by asin.
	 */
	Radian asin(float x);
	/**
	 * @brief Compute the atan of a float.
	 * @param x The value that will be computed.
	 * @return A new radian with the value computed by atan.
	 */
	Radian atan(float x);
	/**
	 * @brief Compute the atan2 of a two floats.
	 * @param y The first value that will be computed.
	 * @param x The second value that will be computed.
	 * @return A new radian with the values computed by atan2.
	 */
	Radian atan2(float y, float x);

	/**
	 * @brief Shortcut for calling Radian
	 */
	typedef Radian Rad;
	/**
	 * @brief Shortcut for calling Degree
	 */
	typedef Degree Deg;
}
