#pragma once

#include "Vector/Vector3.h"
#include "Core/Angle.h"
#include "Core/CMath.h"
namespace LibMath
{
	struct Quaternion
	{
		//----------------------------------------------------------------------Constructors----------------------------------------------------------------------

		/**
		* @brief Default Quaternion constructor, set X,Y,Z,W to 0.f, 0.f, 0.f, 1.f
		*/
		Quaternion();
		/**
		* @brief Quaternion constructor given 4 floats x,y,z,w
		*
		* @param x X Value.
		* @param y Y Value.
		* @param z Z Value.
		* @param w W Value.
		*/
		Quaternion(float x, float y, float z, float w);


		/**
		* @brief Quaternion constructor given an angle and an axis
		*
		* @param angle Angle (In degree for now).
		* @param axis A 3D axis vector.
		*/
		Quaternion(LibMath::Degree angle, LibMath::Vector3& axis);


		/**
		* @brief Quaternion constructor given Euler angle. Default order is XYZ
		*
		* @param pitch Rotation around x-axis.
		* @param yaw Rotation around y-axis.
		* @param roll Rotation around z-axis.
		*/
		Quaternion(LibMath::Radian pitch, LibMath::Radian yaw, LibMath::Radian roll);
		/**
		* @brief Quaternion constructor given Euler angle. Default order is XYZ
		*
		* @param pitch Rotation around x-axis.
		* @param yaw Rotation around y-axis.
		* @param roll Rotation around z-axis.
		* @param order Sequence in which rotation should be apply.
		*/
		Quaternion(LibMath::Radian pitch, LibMath::Radian yaw, LibMath::Radian roll, LibMath::RotationSequence order);

		//----------------------------------------------------------------------Operators----------------------------------------------------------------------
		
		/**
		* @brief Checks if the values of two operands are equal or not, if yes then condition becomes true.
		*
		* @param other Quaternion to compare
		*/
		bool operator==(const Quaternion& other) const;
		/**
		* @brief Checks if the values of two operands are equal or not, if values are not equal then condition becomes true.
		*
		* @param other Quaternion to compare
		*/
		bool operator!=(const Quaternion& other) const;
		/**
		* @brief Simple assignment operator, Assigns values from right side operands to left side operand
		*
		* @param other Quaternion to assign
		*/
		Quaternion operator=(const Quaternion& other);
		/**
		* @brief Adds two operands (Quaternion + Quaternion)
		*
		* @param other Quaternion to add
		*/
		Quaternion operator+(const Quaternion& other) const;
		/**
		* @brief Substract two operands (Quaternion - Quaternion)
		*
		* @param other Quaternion to substract
		*/
		Quaternion operator-(const Quaternion& other) const;
		/**
		* @brief Multiplies both operands (Quaternion * Quaternion)
		*
		* @param other Quaternion to multiply
		*/
		Quaternion operator*(const Quaternion & other) const;
		/**
		* @brief Multiplies both operands (Quaternion * float)
		*
		* @param other float to multiply
		*/
        Quaternion operator*(float f) const;
		/**
		* @brief Multiply AND assignment operator, It multiplies right operand with the left operand (Quaternion * float) and assign the result to left operand.
		*
		* @param other float to multiply
		*/
		Quaternion& operator*=(float f);
		/**
		* @brief Multiply AND assignment operator, It multiplies right operand with the left operand (Quaternion * Quaternion) and assign the result to left operand.
		*
		* @param other Quaternion to multiply
		*/
		Quaternion& operator*=(const Quaternion& other);

		// TODO ADD A UNIT TEST FOR THIS FUNCTION
		/**
		 * @brief Rotate Vector3 (p) by this quaternion (q)
		 * @param other Vector to rotate
		 * @return New Vector3 result of the multiplication (q.p).q^-1
		 */
		Vector3 operator*(const Vector3& other) const;
		// TODO ADD A UNIT TEST FOR THIS FUNCTION // copy of operator*(Vector3) above
		/**
		 * @brief Rotate Vector3 (p) by this quaternion (q)
		 * @param other Vector to rotate
		 * @return New Vector3 result of the multiplication (q.p).q^-1
		 */
		Vector3 Rotate(const Vector3& other) const;
		
		//----------------------------------------------------------------------Functions----------------------------------------------------------------------

		/**
		* @brief Return the dot product
		*
		* @param other Another Quaternion 
		* @return The dot product.
		*/
		float DotProduct(const Quaternion& other) const;
		/**
		* @brief Normalize a quaternion
		*/
		void Normalize();
		/**
		* @brief Return a normalize quaternion
		*
		* @return The normalized quaternion.
		*/
		Quaternion GetNormalize() const;
		/**
		* @brief Conjugate a quaternion from another one
		*
		* @param other Another Quaternion
		*/
		void Conjugate(const Quaternion& other);
		/**
		* @brief Inverse the quaternion
		*/
		void Inverse();

		/**
		 * @brief Multiplie all parameter by -1 to negate the quaternion
		 */
		void Negate();
		/**
		* @brief Return the inversed quaternion
		*
		* @return The inversed quaternion.
		*/
		Quaternion GetInverse() const;
		/**
		* @brief Return Norm of quaternion
		*
		* @return The norm (float).
		*/
		//
		float Norm();
		/**
		* @brief Return pitch angle
		*
		* @return The pitch angle.
		*/
		LibMath::Radian GetPitch() const;
		/**
		* @brief Return yaw angle
		*
		* @return The yaw angle.
		*/
		LibMath::Radian GetYaw() const;
		/**
		* @brief Return roll angle
		*
		* @return The roll angle.
		*/
		LibMath::Radian GetRoll() const;

		////----------------------------------------------------------------------Variables----------------------------------------------------------------------

		/*
		* @name Coordinates
		*/
		/*@{*/
		float X;/**< Vectorial imaginary part X*/
		float Y;/**< Vectorial imaginary part Y*/
		float Z;/**< Vectorial imaginary part Z*/
		float W;/**< Real Part*/
		/*@}*/
		
		
		
	};
}	