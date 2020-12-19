#pragma once

#include "Core/Angle.h"

namespace LibMath
{
    /**
	 * Row structure used to retrieve values from a Matrix3 with brackets.
	 */
	struct row3
	{
		/**
         * Initialize row with pointer on row
         *
         * @param ptr Pointer on row
         */
        explicit row3(float* ptr) : m_ptr(ptr) {}

        /**
		 * Retrieves value in row at given index
		 *
		 * @param idx index of the value to retrieve
		 * @return Value at given index
		 */
		float& operator[](const int idx) const { return m_ptr[idx]; }

		/*
		* @name Pointer on constant row
		*/
		/*@{*/
		float* m_ptr;/**< pointer on constant row*/
		/*@}*/
	};

	/**
     * Row structure used to retrieve constant values from a Matrix3 with brackets.
     */
	struct const_row3
	{
        /**
         * Initialize constant row with pointer on row
         * 
         * @param ptr Pointer on row
         */
        explicit const_row3(const float* ptr) : m_ptr(ptr) {}

        /**
		 * Retrieves value in row at given index
		 * 
		 * @param idx index of the value to retrieve
		 * @return Value at given index
		 */
		float operator[](const int idx) const { return m_ptr[idx]; }


		/*
		* @name Pointer on constant row
		*/
		/*@{*/
		const float* m_ptr;/**< pointer on constant row*/
		/*@}*/
	};

    /**
	 * Matrix3 structure, representing a 3x3 matrix, with all its corresponding operations and basic methods.
	 */
	struct Matrix3
	{
        /**
		 * Default constructor. Initialize every values to 0.f
		 */
		Matrix3() = default;

        /**
		 * Constructor allowing initialization of every values.
		 * 
		 * @param a [0][0] value
		 * @param b [0][1] value
		 * @param c [0][2] value
		 * @param d [1][0] value
		 * @param e [1][1] value
		 * @param f [1][2] value
		 * @param g [2][0] value
		 * @param h [2][1] value
		 * @param i [2][2] value
		 */
		Matrix3(const float& a, const float& b, const float& c, const float& d, const float& e, const float& f, const float& g, const float& h, const float& i);

        /**
		 * Copy constructor
		 * 
		 * @param other Matrix3 to copy
		 */
		Matrix3(Matrix3 const& other) = default;

        /**
		 * Replace current Matrix3 by other Matrix3.
		 * 
		 * @param other Matrix3 to replace current Matrix3 by
		 * @return reference of current Matrix3 after replacement
		 */
		Matrix3& operator=(const Matrix3& other) = default;

        /**
		 * Constructor that initialize every values to 0.f except for the diagonal that is set to the diagonalValue float parameter.
		 * Diagonal values being : [0][0], [1][1], [2][2]
		 * This constructor is useful to retrieve Identity Matrix3.
		 * 
		 * @param diagonalValue float used to set diagonal values
		 */
		Matrix3(const float& diagonalValue);

        /**
		 * Destructor.
		 */
		~Matrix3() = default;

        /**
         * Calculates the determinant of the current Matrix3
         * 
         * @return determinant of current Matrix3
         */
        [[nodiscard]] float Determinant() const;
		
        /**
		 * Gives Identity matrix for 3x3 format matrix
		 * 
		 * @return 3x3 Identity matrix
		 */
		static Matrix3 IdentityMatrix() { return Matrix3(1.f); }

		/**
         * Gives rotation Matrix3 for given Radian.
         *
         * @param rad rotation Radian
         * @return rotation Matrix3 for given Radian
         */
		static Matrix3 RotationMatrix(const Radian& rad);

        /**
		 * Gives the translation Matrix3 of given x and y values
		 * 
		 * @param x Value of the x axis translation
		 * @param y Value of the y axis translation
		 * @return Translation Matrix3 for given values
		 */
		static Matrix3 TranslationMatrix(const float& x, const float& y);

        /**
		 * Gives scale Matrix3 of x and y ratio. Used to scale a Matrix3 by x and y ratio.
		 * 
		 * @param x Scale on the x axis
		 * @param y Scale on the y axis
		 * @return Scale Matrix3 for given ratios
		 */
		static Matrix3 ScaleMatrix(const float& x, const float& y);

        /**
		 * Transposes given Matrix3
		 * 
		 * @param matrix Matrix3 to transpose
		 */
		static void Transpose(Matrix3& matrix);

        /**
		 * Inverses given Matrix3
		 * 
		 * @param matrix Matrix3 to inverse
		 */
		static void Inverse(Matrix3& matrix);

		
        /**
		 * Transposes current Matrix3
		 * 
		 * @return Transposed current Matrix3
		 */
		[[nodiscard]] Matrix3 Transpose() const;


        /**
		 * Inverses current Matrix3
		 * 
		 * @return Inverted current Matrix3
		 */
		[[nodiscard]] Matrix3 Inverse() const;

        /**
         * Translates current Matrix3 by given x and y coordinates
         * 
         * @param x coordinate to translate Matrix3 with
         * @param y coordinate to translate Matrix3 with
         * @return Translated current Matrix3
         */
        [[nodiscard]] Matrix3 Translate(const float& x, const float& y) const;
		
        /**
		 * Rotates current Matrix3 by given Radian rad. Faster than Matrix3 * RotationMatrix(rad).
		 * 
		 * @param rad Radian to rotate current Matrix3 by
		 * @return Rotated current Matrix3
		 */
        [[nodiscard]] Matrix3 Rotate(const Radian& rad) const;

        /**
         * Calculates the Adjugate of a Matrix3
         *
		 * @return Adjugate of the Matrix3
         */
        [[nodiscard]] Matrix3 Adjugate() const;

        /**
         * Scales current Matrix3 by x and y values
		 * 
         * @param x The x coordinate to scale the Matrix by
         * @param y The y coordinate to scale the Matrix by
         * @return Scaled current Matrix3
         */
        [[nodiscard]] Matrix3 Scale(const float& x, const float& y) const;

        /**
		 * Checks equality between current Matrix3 and other Matrix3
		 *
		 * @param other Matrix3 to check equality on
		 * @return bool true if equal, false if not
		 */
		bool operator==(const Matrix3& other) const;

        /**
		 * Checks inequality between current Matrix3 and other Matrix3
		 *
		 * @param other Matrix3 to check inequality on
		 * @return bool false if equal, true if not
		 */
		bool operator!=(const Matrix3& other) const { return !(*this == other); }

        /**
		 * Retrieves row at given index in rows array
		 * 
		 * @param idx index of the row to retrieve
		 * @return Row at index idx
		 */
		row3 operator[](const int idx) { return row3(&m_row[idx * 3]); }

        /**
		 * Retrieves row constant value at given index in rows array
		 * 
		 * @param idx index of the row to retrieve
		 * @return Constant row value at index idx
		 */
		const_row3 operator[](const int idx) const { return const_row3(&m_row[idx * 3]); }

        /**
		 * Adds other Matrix3 to current Matrix3, by adding every single current values to the other corresponding ones.
		 * 
		 * @param other Matrix3 to add to current Matrix3
		 * @return reference on current Matrix3 after addition
		 */
		Matrix3& operator+=(const Matrix3& other);

        /**
		 * Subtracts other Matrix3 from current Matrix3.
		 * 
		 * @param other Matrix3 to subtract from current Matrix3
		 * @return reference on current Matrix3 after subtraction
		 */
		Matrix3& operator-=(const Matrix3& other);

        /**
		 * Multiplies current Matrix3 by other Matrix3.
		 * 
		 * @param other Matrix3 to multiply current Matrix3 by
		 * @return reference on current Matrix3 after multiplication
		 */
		Matrix3& operator*=(const Matrix3& other);

        /**
		 * Divides current Matrix3 by other float. Each current Matrix3 values are divided by other float.
		 * 
		 * @param other float to divide current Matrix3 by
		 * @return reference on current Matrix3 after division
		 */
		Matrix3& operator/=(const float& other);

        /**
		 * Multiplies current Matrix3 by other float. Each current Matrix3 is multiplied by other float.
		 * 
		 * @param other float to multiply current Matrix3 by
		 * @return reference on current Matrix3 after multiplication
		 */
		Matrix3& operator*=(const float& other);

        /**
		 * Adds two Matrix3 together, by adding every single lhs values to the rhs corresponding ones.
		 * 
		 * @param lhs Operator on the left side of the operator
		 * @param rhs Operator on the right side of the operator
		 * @return Matrix3 result of lhs and rhs addition
		 */
		friend Matrix3 operator+(Matrix3 lhs, const Matrix3& rhs);

        /**
		 * Subtracts lhs Matrix3 from rhs Matrix3.
		 * 
		 * @param lhs Operator on the left side of the operator
		 * @param rhs Operator on the right side of the operator
		 * @return Matrix3 result of lhs and rhs subtraction
		 */
		friend Matrix3 operator-(Matrix3 lhs, const Matrix3& rhs);

        /**
		 * Multiplies two Matrix3 together.
		 * 
		 * @param lhs Operator on the left side of the operator
		 * @param rhs Operator on the right side of the operator
		 * @return Matrix3 result after multiplication
		 */
		friend Matrix3 operator*(Matrix3 lhs, const Matrix3& rhs);

        /**
		 * Gives the division result of lhs Matrix3 by rhs float.
		 * 
		 * @param lhs Operator on the left side of the operator
		 * @param rhs Operator on the right side of the operator
		 * @return Matrix3 result after division of lhs by rhs
		 */
		friend Matrix3 operator/(Matrix3 lhs, const float& rhs);

        /**
		 * Gives the multiplication result of lhs Matrix3 by rhs float
		 * 
		 * @param lhs Operator on the left side of the operator
		 * @param rhs Operator on the right side of the operator
		 * @return Matrix3 result after multiplication of rhs by lhs
		 */
		friend Matrix3 operator*(Matrix3 lhs, const float& rhs);

		/*
		* @name Matrix3 values
		*/
		/*@{*/
		float m_row[9]{ 0.f };/**< array containing 9 values of the Matrix3*/
		/*@}*/
	};
}