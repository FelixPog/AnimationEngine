
#define _USE_MATH_DEFINES
#include "Algorithm/CORDIC.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <catch2/catch.hpp>
#include <iostream>
#include "Core/AngleDefine.h"

namespace LibMath
{

    TEST_CASE("trigo in radian", "[trigo][radian]")
    {
        CORDIC::SetPrecision(21);
        const float margin = 1.f / 300000;

        SECTION("acos")
        {
            for (int i = 0; i < 2001; i++)
            {
                float cosValue = i * 0.001f - 1.f;
                //std::cout << "[" << cosValue << "]" << std::endl;
                CHECK(CORDIC::acos_r(cosValue) == Approx(std::acos(cosValue)).margin(margin));
            }
            CHECK(std::isnan(CORDIC::acos_r(-1.1f)));
            CHECK(std::isnan(CORDIC::acos_r(1.1f)));
        }

        SECTION("asin")
        {
            for (int i = 0; i < 2001; i++)
            {
                float sinValue = i * 0.001f - 1.f;
                //std::cout << "[" << sinValue << "]" << std::endl;
                CHECK(CORDIC::asin_r(sinValue) == Approx(std::asin(sinValue)).margin(margin));
            }
            CHECK(std::isnan(CORDIC::asin_r(-1.1f)));
            CHECK(std::isnan(CORDIC::asin_r(1.1f)));
        }

        SECTION("atan")
        {
            for (int i = 0; i < 251; i++)
            {
                float tanValue = i * 10.f - 2500.f;
                //std::cout << "[" << tanValue << "]" << std::endl;
                CHECK(CORDIC::atan_r(tanValue) == Approx(std::atan(tanValue)).margin(margin));
            }
            for (int i = 0; i < 2001; i++)
            {
                float tanValue = i * 0.01f - 10.f;
                //std::cout << "[" << tanValue << "]" << std::endl;
                CHECK(CORDIC::atan_r(tanValue) == Approx(std::atan(tanValue)).margin(margin));
            }
            for (int i = 0; i < 251; i++)
            {
                float tanValue = i * 10.f;
                //std::cout << "[" << tanValue << "]" << std::endl;
                CHECK(CORDIC::atan_r(tanValue) == Approx(std::atan(tanValue)).margin(margin));
            }
        }

        SECTION("cos")
        {
            for (int i = -20; i < 6500; i++)
            {
                float angle = i * 0.01f;
                //std::cout << "[" << angle << "]" << std::endl;
                CHECK(CORDIC::cos_r(angle) == Approx(std::cos(angle)).margin(margin));
            }
            CHECK(CORDIC::cos_r(-15.f) == Approx(std::cosf(-15.f)).margin(margin));
            CHECK(CORDIC::cos_r(0.00001f) == Approx(std::cosf(0.00001f)).margin(margin));
            CHECK(CORDIC::cos_r(100.f) == Approx(std::cosf(100.f)).margin(margin));
        }

        SECTION("sin")
        {
            for (int i = -20; i < 6500; i++)
            {
                float angle = i * 0.01f;
                //std::cout << "[" << angle << "]" << std::endl;
                CHECK(CORDIC::sin_r(angle) == Approx(std::sin(angle)).margin(margin));
            }
            CHECK(CORDIC::sin_r(-15.f) == Approx(std::sinf(-15.f)).margin(margin));
            CHECK(CORDIC::sin_r(0.00001f) == Approx(std::sinf(0.00001f)).margin(margin));
            CHECK(CORDIC::sin_r(100.f) == Approx(std::sinf(100.f)).margin(margin));
        }

        SECTION("tan")
        {
            // tan = sin / cos
            // Any imprecision of cos specialy when cos is really small can change the result of tan a lot.
            // The 14 fail test case are not clutter around any value. No guess on what append could be made.
            // Althought the algorithm is the same as the one use with degree, radian test 1.8 time more values.
            // So step are 1.8 smaller.

            for (int i = -20; i < 6500; i++)
            {
                float angle = i * 0.01f;
                //std::cout << "[" << angle << "]" << std::endl;
                CHECK(CORDIC::tan_r(angle) == Approx(std::tan(angle)).epsilon(100.f * margin).margin(margin));
            }
            CHECK(CORDIC::tan_r(-15.f) == Approx(std::tanf(-15.f)).epsilon(100.f * margin).margin(margin));
            CHECK(CORDIC::tan_r(0.00001f) == Approx(std::tanf(0.00001f)).epsilon(100.f * margin).margin(margin));
            CHECK(CORDIC::tan_r(100.f) == Approx(std::tanf(100.f)).epsilon(100.f * margin).margin(margin));
        }
    }


    TEST_CASE("trigo in degree", "[trigo][degree]")
    {
        CORDIC::SetPrecision(21);
        const float margin = 1.f / 300000;
        const float tanMargin = 1.f / 100000;

        SECTION("acos")
        {
            for (int i = 0; i < 2001; i++)
            {
                float cosValue = i * 0.001f - 1.f;
                //std::cout << "[" << cosValue << "]" << std::endl;
                CHECK(CORDIC::acos_0(cosValue) == Approx(std::acos(cosValue) * 180.0 / M_PI).margin(margin));
            }
            CHECK(std::isnan(CORDIC::acos_0(-1.1f)));
            CHECK(std::isnan(CORDIC::acos_0(1.1f)));
        }

        SECTION("asin")
        {
            // asin_0 (in degree) fail to be precise to the fifth significant digit 79 times
            // around zero (from -0.073 to 0.068). I suspect a problem with the square root
            // involve but it work just fine for asin_r, acos_r, atan_r, acos0 and atan_0 so
            // I have no clues how to explain all those faillure since they represent almost
            // 1/5 of all faillure.
            for (int i = 0; i < 2001; i++)
            {
                float sinValue = i * 0.001f - 1.f;
                //std::cout << "[" << sinValue << "]" << std::endl;
                CHECK(CORDIC::asin_0(sinValue) == Approx(std::asin(sinValue) * 180.0 / M_PI).margin(margin));
            }
            CHECK(std::isnan(CORDIC::asin_0(-1.1f)));
            CHECK(std::isnan(CORDIC::asin_0(1.1f)));
        }

        SECTION("atan")
        {
            // atan_0 (in degree) fail to be precise to the fifth significant digit 8 times
            // around zero (from -0.03 to 0.06). Given atan varies the most the closer it
            // is from 0 and that atan_0 is basically the same as atan_r (in radian), I
            // suspect the error is due to converting from radian to degree to test values.

            for (int i = 0; i < 251; i++)
            {
                float tanValue = i * 10.f - 2500.f;
                //std::cout << "[" << tanValue << "]" << std::endl;
                CHECK(CORDIC::atan_0(tanValue) == Approx(std::atan(tanValue) * 180.0 / M_PI).margin(margin));
            }
            for (int i = 0; i < 2001; i++)
            {
                float tanValue = i * 0.01f - 10.f;
                //std::cout << "[" << tanValue << "]" << std::endl;
                CHECK(CORDIC::atan_0(tanValue) == Approx(std::atan(tanValue) * 180.0 / M_PI).margin(margin));
            }
            for (int i = 0; i < 251; i++)
            {
                float tanValue = i * 10.f;
                //std::cout << "[" << tanValue << "]" << std::endl;
                CHECK(CORDIC::atan_0(tanValue) == Approx(std::atan(tanValue) * 180.0 / M_PI).margin(margin));
            }
        }

        SECTION("cos")
        {
            for (int i = -20; i < 3620; i++)
            {
                float angle = i * 0.1f;
                //std::cout << "[" << angle << "]" << std::endl;
                CHECK(CORDIC::cos_0(angle) == Approx(std::cos((double)angle * M_PI / 180.0)).margin(margin));
            }

            CHECK(CORDIC::cos_0(-3500.f) == Approx(std::cosf(-3500.f * (float)M_PI / 180.f)).margin(margin));
            CHECK(CORDIC::cos_0(0.00001f) == Approx(std::cosf(0.00001f * (float)M_PI / 180.f)).margin(margin));
            CHECK(CORDIC::cos_0(600.f) == Approx(std::cosf(600.f * (float)M_PI / 180.f)).margin(margin));
        }

        SECTION("sin")
        {
            for (int i = -20; i < 3620; i++)
            {
                float angle = i * 0.1f;
                //std::cout << "[" << angle << "]" << std::endl;
                CHECK(CORDIC::sin_0(angle) == Approx(std::sin((double)angle * M_PI / 180.0)).margin(margin));
            }

            CHECK(CORDIC::sin_0(-3500.f) == Approx(std::sinf(-3500.f * (float)M_PI / 180.f)).margin(margin));
            CHECK(CORDIC::sin_0(0.00001f) == Approx(std::sinf(0.00001f * (float)M_PI / 180.f)).margin(margin));
            CHECK(CORDIC::sin_0(600.f) == Approx(std::sinf(600.f * (float)M_PI / 180.f)).margin(margin));
        }

        SECTION("tan")
        {
            for (int i = -20; i < 3620; i++)
            {
                float angle = i * 0.1f;
                //std::cout << "[" << angle << "]" << std::endl;
                CHECK(CORDIC::tan_0(angle) == Approx(std::tan((double)angle * M_PI / 180.0)).epsilon(100.f * margin).margin(margin));
            }

            CHECK(CORDIC::tan_0(-3500.f) == Approx(std::tanf(-3500.f * (float)M_PI / 180.f)).epsilon(100.f * margin).margin(margin));
            CHECK(CORDIC::tan_0(0.00001f) == Approx(std::tanf(0.00001f * (float)M_PI / 180.f)).epsilon(100.f * margin).margin(margin));
            CHECK(CORDIC::tan_0(600.f) == Approx(std::tanf(600.f * (float)M_PI / 180.f)).epsilon(100.f * margin).margin(margin));
        }
    }
}