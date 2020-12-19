#include "Quaternion/Quaternion.h"
#include <catch2/catch.hpp>
#include <glm/gtc/quaternion.hpp>

namespace LibMath
{
    TEST_CASE("Quaternion constructors", "[Quaternion][Constructor]")
    {
        SECTION("Quaternion Default Constructor")
        {
            Quaternion q1;

            REQUIRE(q1.X == 0.f);
            REQUIRE(q1.Y == 0.f);
            REQUIRE(q1.Z == 0.f);
            REQUIRE(q1.W == 1.f);
            
        }

        SECTION("Quaternion Given 4 floats")
        {
            Quaternion q1(7.f, 2.f, 4.f, 1.f);

            REQUIRE(q1.X == 7.f);
            REQUIRE(q1.Y == 2.f);
            REQUIRE(q1.Z == 4.f);
            REQUIRE(q1.W == 1.f);

        }

        SECTION("Quaternion Given an angle and an axis")
        {
            float degree = 180;
            
            Degree angle(degree);

            Vector3 axis(1.f, 1.f, 1.f);


            Quaternion q1(angle, axis);

            REQUIRE(q1.X == 1.f);
            REQUIRE(q1.Y == 1.f);
            REQUIRE(q1.Z == 1.f);
            //Using approximation cause std::cos(90 deg) do not return exactly 0 because it converts to radian and pi/2 is 1.57... and many more numbers behind
            Approx target = Approx(0.0f).margin(0.0000002f);
            REQUIRE(q1.W == target);
        }

        SECTION("Quaternion Given Euler angle")
        {
            Quaternion quaternion(Radian(15.f), Radian(65.f), Radian(40.f));
            Quaternion quaternion2(Radian(15.f), Radian(65.f), Radian(40.f), RotationSequence::XYZ);

            Radian pitch = quaternion.GetPitch();
            Radian yaw = quaternion.GetYaw();
            Radian roll = quaternion.GetRoll();

            quaternion2 = Quaternion(pitch, yaw, roll);

            glm::vec3 euler(15.f, 65.f, 40.f);
            glm::quat glm(euler);
            glm::mat4 glmmat(glm);

            float glmpitch = glm::pitch(glm);
            float glmyaw = glm::yaw(glm);
            float glmroll = glm::roll(glm);

            int i = 0;
               i++;
        }
    }

    TEST_CASE("Quaternion operators", "[Quaternion][Operator]")
    {
        SECTION("Quaternion operator == Quaternion")
        {
            Quaternion q1;
            Quaternion q2;
            Quaternion q3(7.f, 2.f, 4.f, 1.f);

            REQUIRE((q1 == q2) == true);
            REQUIRE((q2 == q3) == false);
            REQUIRE((q1 == q3) == false);

        }

        SECTION("Quaternion operator != Quaternion")
        {
            Quaternion q1;
            Quaternion q2;
            Quaternion q3(7.f, 2.f, 4.f, 1.f);

            REQUIRE((q1 != q2) == false);
            REQUIRE((q2 != q3) == true);
            REQUIRE((q1 != q3) == true);

        }

        SECTION("Quaternion operator = Quaternion")
        {
            Quaternion q1;
            Quaternion q2(7.f, 2.f, 4.f, 1.f);

            REQUIRE((q1 == q2) == false);

            q1 = q2;

            REQUIRE((q1 == q2) == true);

        }

        SECTION("Quaternion operator + Quaternion")
        {
            Quaternion ExpectedResult(7.f, 2.f, 4.f, 1.f);

            Quaternion q1(2.f, 1.f, 2.f, 1.f);
            Quaternion q2(5.f, 1.f, 2.f, 0.f);
            Quaternion q3 = q1 + q2;

            REQUIRE(q3 == ExpectedResult);
        }

        SECTION("Quaternion operator - Quaternion")
        {
            Quaternion ExpectedResult(-3.f, 0.f, 0.f, 1.f);

            Quaternion q1(2.f, 1.f, 2.f, 1.f);
            Quaternion q2(5.f, 1.f, 2.f, 0.f);
            Quaternion q3 = q1 - q2;

            REQUIRE(q3 == ExpectedResult);
        }

        SECTION("Quaternion operator * Quaternion")
        {
            Quaternion ExpectedResult(9.f, 5.f, -3.f, -15.f);

            Quaternion q1(2.f, 2.f, 1.f, 1.f);
            Quaternion q2(5.f, 2.f, 2.f, 1.f);
            Quaternion q3 = q1 * q2;

            REQUIRE(q3 == ExpectedResult);

        }

        SECTION("Quaternion operator * float")
        {
            Quaternion ExpectedResult(6.f, 6.f, 3.f, 3.f);
            Quaternion q1(2.f, 2.f, 1.f, 1.f);
            float f = 3;

            Quaternion q2 = q1 * f;

            REQUIRE(q2 == ExpectedResult);
        }

        SECTION("Quaternion operator *= float")
        {
            Quaternion ExpectedResult(6.f, 6.f, 3.f, 3.f);

            Quaternion q1(2.f, 2.f, 1.f, 1.f);
            float f = 3;

            q1 *= f;

            REQUIRE(q1 == ExpectedResult);
        }

        SECTION("Quaternion operator *= Quaternion")
        {
            Quaternion ExpectedResult(9.f, 5.f, -3.f, -15.f);

            Quaternion q1(2.f, 2.f, 1.f, 1.f);
            Quaternion q2(5.f, 2.f, 2.f, 1.f);
            q1 *= q2;

            REQUIRE(q1 == ExpectedResult);
        }
    }

    TEST_CASE("Quaternion functions", "[Quaternion][Functions]")
    {
        SECTION("Quaternion DotProduct")
        {
            float ExpectedResult = 17;

            Quaternion q1(2.f, 2.f, 1.f, 1.f);
            Quaternion q2(5.f, 2.f, 2.f, 1.f);

            REQUIRE(q1.DotProduct(q2) == ExpectedResult);
        }

        SECTION("Quaternion Normalize")
        {
            Quaternion ExpectedResult(0.5f, 0.5f, 0.5f, 0.5f);

            Quaternion q1(1.f, 1.f, 1.f, 1.f);

            q1.Normalize();

            REQUIRE(q1 == ExpectedResult);

            Quaternion q2(2.f, 2.f, 2.f, 2.f);

            q2.Normalize();

            REQUIRE(q2 == ExpectedResult);
        }

        SECTION("Quaternion GetNormalize")
        {
            Quaternion ExpectedResult(0.5f, 0.5f, 0.5f, 0.5f);
            Quaternion ExpectedResult2(0.f, 0.f, 0.f, 1.f);

            Quaternion q1(1.f, 1.f, 1.f, 1.f);
            Quaternion q2(0.f, 0.f, 0.f, 0.f);

            Quaternion q3 = q1.GetNormalize();

            Quaternion q4 = q2.GetNormalize();

            REQUIRE(q3 == ExpectedResult);
            REQUIRE(q1 != q3);

            REQUIRE(q4 == ExpectedResult2);
            REQUIRE(q2 != q4);

        }

        SECTION("Quaternion Conjugate")
        {
            Quaternion ExpectedResult(-3.f, -3.f, -3.f, 1.f);

            Quaternion q1(1.f, 1.f, 1.f, 1.f);
            Quaternion q2(3.f, 3.f, 3.f, 1.f);

            q1.Conjugate(q2);

            REQUIRE(q1 == ExpectedResult);
        }

        SECTION("Quaternion Inverse")
        {
            Quaternion ExpectedResult(-7.f, -2.f, -4.f, 1.f);

            Quaternion q1(7.f, 2.f, 4.f, 1.f);

            q1.Inverse();

            REQUIRE(q1 == ExpectedResult);
        }

        SECTION("Quaternion GetInverse")
        {
            Quaternion ExpectedResult(-7.f, -2.f, -4.f, 1.f);

            Quaternion q1(7.f, 2.f, 4.f, 1.f);

            Quaternion q2 = q1.GetInverse();

            REQUIRE(q2 == ExpectedResult);
            REQUIRE(q1 != q2);
        }

        SECTION("Quaternion Norm")
        {
            float ExpectedResult = 4;

            Quaternion q1(2.f, 2.f, 2.f, 2.f);

            REQUIRE(q1.Norm() == ExpectedResult);
        }
    }

}
