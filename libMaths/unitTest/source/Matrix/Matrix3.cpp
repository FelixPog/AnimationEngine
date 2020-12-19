#include "Matrix/Matrix3.h"

#include <catch2/catch.hpp>

#include "Vector/Vector3.h"

namespace LibMath
{

    TEST_CASE("Matrix3 Construction", "[matrix][matrix3]")
    {
        Matrix3 testMat;

        SECTION("Default constructor")
        {
            for (float i : testMat.m_row)
            {
                REQUIRE(i == 0.f);
            }
        }


        SECTION("Copy constructor")
        {
            testMat.m_row[2] = 256.f;
            testMat.m_row[3] = 145.f;
            testMat.m_row[5] = 185.f;
            testMat.m_row[7] = 420.f;
            testMat.m_row[8] = 1984.f;
            const Matrix3 testMat2(testMat);
            
            for (auto i = 0; i < 9; ++i)
            {
                REQUIRE(testMat.m_row[i] == testMat2.m_row[i]);
            }
        }

    }

    TEST_CASE("Matrix3 Identity", "[matrix][matrix3]")
    {
        const Matrix3 mat3Identity = {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        };

        REQUIRE(Matrix3::IdentityMatrix() == mat3Identity);

    }

    TEST_CASE("Matrix3 Equality", "[matrix][matrix3][operation]")
    {
        const Matrix3 testMat1;
        Matrix3 testMat2;
        const Matrix3 testMat3 = {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        };

        SECTION("Check difference with self")
        {
            // Check equality with self
            REQUIRE(testMat1 == testMat1);
        }

        SECTION("Check difference with equal matrix")
        {
            // Check equality with other equal matrix
            REQUIRE(testMat1 == testMat2);
        }

        SECTION("Check difference with different matrix")
        {
            // Check difference with other different matrix
            REQUIRE(testMat1 != testMat3);
        }

        SECTION("Changing single value")
        {
            // Check difference after changing a value
            testMat2.m_row[0] = 1.f;
            REQUIRE(testMat1 != testMat2);
        }
    }

    TEST_CASE("Matrix3 Addition", "[matrix][matrix3][operation]")
    {
        Matrix3 testMat1 = {
            1.f, 0.f, 5.f,
            2.f, 1.f, 6.f,
            3.f, 4.f, 0.f
        };

        Matrix3 testMat2 = {
            -24.f, 20.f, -5.f,
            18.f, -15.f, 4.f,
            5.f, -4.f, 1.f
        };

        Matrix3 expectedResultAddition = {
            -23.f, 20.f, 0.f,
            20.f, -14.f, 10.f,
            8.f, 0.f, 1.f
        };

        SECTION("Simple addition")
        {
            REQUIRE(testMat1 + testMat2 == expectedResultAddition);
        }

        SECTION("Addition with direct replacement")
        {
            testMat1 += testMat2;

            REQUIRE(testMat1 == expectedResultAddition);
        }

    }

    TEST_CASE("Matrix3 Substraction", "[matrix][matrix3][operation]")
    {
        Matrix3 testMat1 = {
            1.f, 0.f, 5.f,
            2.f, 1.f, 6.f,
            3.f, 4.f, 0.f
        };

        Matrix3 testMat2 = {
            -24.f, 20.f, -5.f,
            18.f, -15.f, 4.f,
            5.f, -4.f, 1.f
        };

        Matrix3 expectedResultAddition = {
            25.f, -20.f, 10.f,
            -16.f, 16.f, 2.f,
            -2.f, 8.f, -1.f
        };

        SECTION("Simple substraction")
        {
            REQUIRE(testMat1 - testMat2 == expectedResultAddition);
        }

        SECTION("Substraction on self")
        {
            REQUIRE(testMat1 - testMat1 == Matrix3());
            // Matrix - Matrix = Matrix{0}
        }

        SECTION("Substraction with direct replacement")
        {
            testMat1 -= testMat2;

            REQUIRE(testMat1 == expectedResultAddition);
        }
    }

    TEST_CASE("Matrix3 Multiplication", "[matrix][matrix3][operation]")
    {
        const Matrix3 testMat1 = {
            2, 2, 2,
            2, 2, 2,
            2, 2, 2
        };

        const Matrix3 testMat2 = {
            1, 1, 1,
            2, 2, 2,
            3, 3, 3
        };

        const Matrix3 expectedResult = {
            6, 6, 6,
            12, 12, 12,
            18, 18, 18
        };

        const Matrix3 multiplicationResult = testMat1 * testMat2;

        REQUIRE(multiplicationResult == expectedResult);

    }

    TEST_CASE("Matrix3 Transpose", "[matrix][matrix3]")
    {
        const Matrix3 testMat3 = {
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
        };

        const Matrix3 expectedResultMat3 = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        };

        SECTION("Simple Transpose")
        {
            REQUIRE(testMat3.Transpose() == expectedResultMat3);
        }

        SECTION("Transpose multiplication equality with self")
        {
            REQUIRE((testMat3 * testMat3).Transpose() == testMat3.Transpose() * testMat3.Transpose());
        }
    }

    TEST_CASE("Matrix3 Determinant", "[matrix][matrix3]")
    {
        Matrix3 testMat1 = {
            -2, -1, 2,
            2, 1, 0,
            -3, 3, -1
        };


        Matrix3 testMat2 = {
            1, 0, 1,
            1, 1, 0,
            0, 0, 0
        };

        SECTION("Determinant calculation")
        {
            REQUIRE(testMat1.Determinant() == 18.f);
            REQUIRE(testMat2.Determinant() == 0.f);
        }

        SECTION("Matrix determinant same as Transpose determinant")
        {
            REQUIRE(testMat1.Determinant() == testMat1.Transpose().Determinant());
        }
    }


    TEST_CASE("Matrix3 Adjugate", "[matrix][matrix3]")
    {
        Matrix3 testMat3 = {
            1.f, 0.f, 5.f,
            2.f, 1.f, 6.f,
            3.f, 4.f, 0.f
        };


        Matrix3 exceptedResultInverse = {
            -24.f, 20.f, -5.f,
            18.f, -15.f, 4.f,
            5.f, -4.f, 1.f
        };

        REQUIRE(testMat3.Adjugate() == exceptedResultInverse);
    }

    TEST_CASE("Matrix3 Inverse", "[matrix][matrix3]")
    {
        Matrix3 testMat3 = {
            3.f, 2.f, 0.f,
            0.f, 0.f, 1.f,
            2.f, -2.f, 1.f
        };


        Matrix3 exceptedResultInverse = {
            0.2f, -0.2f, 0.2f,
            0.2f, 0.3f, -0.3f,
            0.f, 1.f, 0.f
        };

        SECTION("Inverse simple matrix")
        {
            REQUIRE(testMat3.Inverse() == exceptedResultInverse);
        }

        SECTION("Matrix multiplied by its inverse is equal to the identity matrix")
        {
            REQUIRE(testMat3.Inverse() * testMat3 == Matrix3::IdentityMatrix());
        }
    }

    TEST_CASE("Matrix3 Rotation", "[matrix][matrix3]")
    {
        const Matrix3 testMat1 = {
            3.f, 2.f, 0.f,
            0.f, 0.f, 1.f,
            2.f, -2.f, 1.f
        };

        SECTION("Compare rotate function to rotationMatrix")
        {
            REQUIRE(testMat1.Rotate(Radian(Degree(90).rad())) == testMat1 * Matrix3::RotationMatrix(Radian(Degree(90).rad())));
        }
    }

    TEST_CASE("Matrix3 Scale", "[matrix][matrix3]")
    {
        Matrix3 testMat1 = {
            3.f, 2.f, 0.f,
            0.f, 0.f, 1.f,
            2.f, -2.f, 1.f
        };


        Matrix3 exceptedResultRotation = {
            12.f, 8.f, 0.f,
            0.f, 0.f, 4.f,
            2.f, -2.f, 1.f
        };

        SECTION("Scale simple matrix")
        {
            REQUIRE(testMat1.Scale(4, 4) == exceptedResultRotation);
        }
    }
}
