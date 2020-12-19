#include "Core/Angle.h"

#define _USE_MATH_DEFINES
#include <cmath>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/detail/setup.hpp>
#include <glm/glm.hpp>

#include <catch2/catch.hpp>

namespace LibMath
{
    TEST_CASE("Angle construction", "[angle]")
    {
        SECTION("Default constructor")
        {
            Degree deg;
        	
            CHECK(deg.data == 0.f);

            Radian rad;

            CHECK(rad.data == 0.f);
        }

        SECTION("Param constructor")
        {
            Degree deg(5.f);

            CHECK(deg.data == 5.f);

            Radian rad = Radian(5.f);

            CHECK(rad.data == 5.f);
        }

        SECTION("Copy constructor")
        {
            Degree deg;
            deg = Degree(5.f);

            CHECK(deg.data == 5.f);

            Radian rad;
        	rad = Radian(5.f);

            CHECK(rad.data == 5.f);
        }

        SECTION("Conversion constructor")
        {
            Degree deg(5.f);
            Radian radFromDeg(deg);

            CHECK(radFromDeg.data == Approx(glm::radians(5.f)));

            Radian rad = Radian(5.f);
            Degree degFromRad = Radian(rad);

            CHECK(degFromRad.data == Approx(glm::degrees(5.f)));
        }

        SECTION("Conversion assignator")
        {
            Radian radFromDeg;
        	radFromDeg = Degree(5.f);

            CHECK(radFromDeg.data == Approx(glm::radians(5.f)));

            Degree degFromRad;
        	degFromRad = Radian(5.f);

            CHECK(degFromRad.data == Approx(glm::degrees(5.f)));
        }
    }
	

    TEST_CASE("Angle clamping", "[angle]")
    {
        SECTION("Degree")
        {
            Degree moreThanOneCircle(45.f + 3 * CIRCLE_DEGREE);
            Degree lessThanOneCircle(45.f);
            Degree negativeLessThanOneCircle(45.f - CIRCLE_DEGREE);
            Degree negativeMoreThanOneCircle(45.f - 3 * CIRCLE_DEGREE);

        	SECTION("Clamp")
        	{             
                moreThanOneCircle.Clamp();
                lessThanOneCircle.Clamp();
                negativeLessThanOneCircle.Clamp();
                negativeMoreThanOneCircle.Clamp();
        		
                CHECK(moreThanOneCircle.data == 45.f);
                CHECK(lessThanOneCircle.data == 45.f);
                CHECK(negativeLessThanOneCircle.data == 45.f);
                CHECK(negativeMoreThanOneCircle.data == 45.f);
        	}

        	SECTION("ClampDeg")
        	{
                CHECK(moreThanOneCircle.clampDeg() == 45.f);        		
                CHECK(lessThanOneCircle.clampDeg() == 45.f);
                CHECK(negativeLessThanOneCircle.clampDeg() == 45.f);
                CHECK(negativeMoreThanOneCircle.clampDeg() == 45.f);

                CHECK(moreThanOneCircle.data == 45.f + 3 * CIRCLE_DEGREE);
                CHECK(lessThanOneCircle.data == 45.f);
                CHECK(negativeLessThanOneCircle.data == 45.f - CIRCLE_DEGREE);
                CHECK(negativeMoreThanOneCircle.data == 45.f - 3 * CIRCLE_DEGREE);
        	}

        	SECTION("ClampRad")
        	{
                CHECK(moreThanOneCircle.clampRad() == Approx(glm::radians(45.f)));
                CHECK(lessThanOneCircle.clampRad() == Approx(glm::radians(45.f)));
                CHECK(negativeLessThanOneCircle.clampRad() == Approx(glm::radians(45.f)));
                CHECK(negativeMoreThanOneCircle.clampRad() == Approx(glm::radians(45.f)));

                CHECK(moreThanOneCircle.data == 45.f + 3 * CIRCLE_DEGREE);
                CHECK(lessThanOneCircle.data == 45.f);
                CHECK(negativeLessThanOneCircle.data == 45.f - CIRCLE_DEGREE);
                CHECK(negativeMoreThanOneCircle.data == 45.f - 3 * CIRCLE_DEGREE);
        	}
        }
    	
        SECTION("Radian")
        {
            Radian moreThanOneCircle(glm::radians(45.f) + 3 * CIRCLE_RADIAN);
            Radian lessThanOneCircle(glm::radians(45.f));
            Radian negativeLessThanOneCircle(glm::radians(45.f) - CIRCLE_RADIAN);
            Radian negativeMoreThanOneCircle(glm::radians(45.f) - 3 * CIRCLE_RADIAN);

            SECTION("Clamp")
            {
                moreThanOneCircle.Clamp();
                lessThanOneCircle.Clamp();
                negativeLessThanOneCircle.Clamp();
                negativeMoreThanOneCircle.Clamp();

                CHECK(moreThanOneCircle.data == Approx(glm::radians(45.f)));
                CHECK(lessThanOneCircle.data == Approx(glm::radians(45.f)));
                CHECK(negativeLessThanOneCircle.data == Approx(glm::radians(45.f)));
                CHECK(negativeMoreThanOneCircle.data == Approx(glm::radians(45.f)));
            }

            SECTION("ClampDeg")
            {
                CHECK(moreThanOneCircle.clampDeg() == Approx(45.f));
                CHECK(lessThanOneCircle.clampDeg() == Approx(45.f));
                CHECK(negativeLessThanOneCircle.clampDeg() == Approx(45.f));
                CHECK(negativeMoreThanOneCircle.clampDeg() == Approx(45.f));

                CHECK(moreThanOneCircle.data == Approx(glm::radians(45.f) + 3 * CIRCLE_RADIAN));
                CHECK(lessThanOneCircle.data == Approx(glm::radians(45.f)));
                CHECK(negativeLessThanOneCircle.data == Approx(glm::radians(45.f) - CIRCLE_RADIAN));
                CHECK(negativeMoreThanOneCircle.data == Approx(glm::radians(45.f) - 3 * CIRCLE_RADIAN));
            }

            SECTION("ClampRad")
            {
                CHECK(moreThanOneCircle.clampRad() == Approx(glm::radians(45.f)));
                CHECK(lessThanOneCircle.clampRad() == Approx(glm::radians(45.f)));
                CHECK(negativeLessThanOneCircle.clampRad() == Approx(glm::radians(45.f)));
                CHECK(negativeMoreThanOneCircle.clampRad() == Approx(glm::radians(45.f)));

                CHECK(moreThanOneCircle.data == Approx(glm::radians(45.f) + 3 * CIRCLE_RADIAN));
                CHECK(lessThanOneCircle.data == Approx(glm::radians(45.f)));
                CHECK(negativeLessThanOneCircle.data == Approx(glm::radians(45.f) - CIRCLE_RADIAN));
                CHECK(negativeMoreThanOneCircle.data == Approx(glm::radians(45.f) - 3 * CIRCLE_RADIAN));
            }
        }
    }

	
    TEST_CASE("Angle get", "[angle]")
    {
    	SECTION("Degree")
    	{
            Degree moreThanOneCircle(45.f + 3 * CIRCLE_DEGREE);
            Degree lessThanOneCircle(45.f);
            Degree negativeLessThanOneCircle(45.f - CIRCLE_DEGREE);
            Degree negativeMoreThanOneCircle(45.f - 3 * CIRCLE_DEGREE);

            CHECK(moreThanOneCircle.deg() == 45.f + 3 * CIRCLE_DEGREE);
            CHECK(lessThanOneCircle.deg() == 45.f);
            CHECK(negativeLessThanOneCircle.deg() == 45.f - CIRCLE_DEGREE);
            CHECK(negativeMoreThanOneCircle.deg() == 45.f - 3 * CIRCLE_DEGREE);
    		
            CHECK(moreThanOneCircle.rad() == Approx(glm::radians(45.f + 3 * CIRCLE_DEGREE)));
            CHECK(lessThanOneCircle.rad() == Approx(glm::radians(45.f)));
            CHECK(negativeLessThanOneCircle.rad() == Approx(glm::radians(45.f - CIRCLE_DEGREE)));
            CHECK(negativeMoreThanOneCircle.rad() == Approx(glm::radians(45.f - 3 * CIRCLE_DEGREE)));
    	}

        SECTION("Radian")
        {
            Radian moreThanOneCircle(glm::radians(45.f) + 3 * CIRCLE_RADIAN);
            Radian lessThanOneCircle(glm::radians(45.f));
            Radian negativeLessThanOneCircle(glm::radians(45.f) - CIRCLE_RADIAN);
            Radian negativeMoreThanOneCircle(glm::radians(45.f) - 3 * CIRCLE_RADIAN);

            CHECK(moreThanOneCircle.deg() == Approx(45.f + glm::degrees(3 * CIRCLE_RADIAN)));
            CHECK(lessThanOneCircle.deg() == Approx(45.f));
            CHECK(negativeLessThanOneCircle.deg() == Approx(45.f + glm::degrees(-CIRCLE_RADIAN)));
            CHECK(negativeMoreThanOneCircle.deg() == Approx(45.f + glm::degrees(-3 * CIRCLE_RADIAN)));

            CHECK(moreThanOneCircle.rad() == Approx(glm::radians(45.f) + 3 * CIRCLE_RADIAN));
            CHECK(lessThanOneCircle.rad() == Approx(glm::radians(45.f)));
            CHECK(negativeLessThanOneCircle.rad() == Approx(glm::radians(45.f) - CIRCLE_RADIAN));
            CHECK(negativeMoreThanOneCircle.rad() == Approx(glm::radians(45.f) - 3 * CIRCLE_RADIAN));
        }
    }
	

    TEST_CASE("Angle comparaison", "[angle]")
    {
        SECTION("Degree")
        {
            Degree deg540 = Degree(540.f);
            Degree deg180 = Degree(180.f);
            Degree deg90 = Degree(90.f);
        	
            SECTION("Is equal")
            {
                Degree deg540_two(540.f);

                CHECK(deg540_two == deg540);
                CHECK(deg540 == deg540_two);
                CHECK_FALSE(deg540 == deg90);
                CHECK_FALSE(deg90 == deg540);
            }

            SECTION("Is not equal")
            {
                Degree deg190 = Degree(190.f);
                Degree deg190_two = Degree(190.f);

                CHECK(deg180 != deg190);
                CHECK(deg190 != deg180);
                CHECK_FALSE(deg190 != deg190_two);
                CHECK_FALSE(deg190_two != deg190);
            }

        	SECTION("Is inferior")
            {
                CHECK(deg90 < deg180);
                CHECK_FALSE(deg180 < deg90);
            }

            SECTION("Is superior")
            {
                CHECK(deg180 > deg90);
                CHECK_FALSE(deg90 > deg180);
            }

            SECTION("Is inferior or equal")
            {
                CHECK(deg90 <= deg180);
                CHECK_FALSE(deg180 <= deg90);

                deg540.Clamp();

                CHECK(deg540 <= deg180);
                CHECK(deg180 <= deg540);
            }

            SECTION("Is superior or equal")
            {
                CHECK(deg180 >= deg90);
                CHECK_FALSE(deg90 >= deg180);

                deg540.Clamp();

                CHECK(deg180 >= deg540);
                CHECK(deg540 >= deg180);
            }
        }

    	SECTION("Radian")
        {
            Radian radPi6AndCircle = Radian(glm::radians(30.f) + CIRCLE_RADIAN);
            Radian radPi6 = Radian(glm::radians(30.f));
            Radian radPi2 = Radian(glm::radians(90.f));

            SECTION("Is equal")
            {
                Radian radPi6_two(glm::radians(30.f));

                CHECK(radPi6 == radPi6_two);
                CHECK(radPi6_two == radPi6);
                CHECK_FALSE(radPi6 == radPi2);
                CHECK_FALSE(radPi2 == radPi6);
            }

            SECTION("Is not equal")
            {
                Radian radPi5 = Radian(glm::radians(36.f));
                Radian radPi5_two = Radian(glm::radians(36.f));

                CHECK(radPi6 != radPi5);
                CHECK(radPi5 != radPi6);
                CHECK_FALSE(radPi5 != radPi5_two);
                CHECK_FALSE(radPi5_two != radPi5);
            }

            SECTION("Is inferior")
            {
                CHECK(radPi6 < radPi2);
                CHECK_FALSE(radPi2 < radPi6);
            }

            SECTION("Is superior")
            {
                CHECK(radPi2 > radPi6);
                CHECK_FALSE(radPi6 > radPi2);
            }

            SECTION("Is inferior or equal")
            {
                CHECK(radPi6 <= radPi2);
                CHECK_FALSE(radPi2 <= radPi6);

                radPi6AndCircle.Clamp();

                CHECK(radPi6AndCircle <= radPi6);
                CHECK(radPi6 <= radPi6AndCircle);
            }

            SECTION("Is superior or equal")
            {
                CHECK(radPi2 >= radPi6);
                CHECK_FALSE(radPi6 >= radPi2);

                radPi6AndCircle.Clamp();

                CHECK(radPi6 >= radPi6AndCircle);
                CHECK(radPi6AndCircle >= radPi6);
            }
        }

    	SECTION("Degree and Radian")
        {
            Degree deg180 = Degree(180.f);
            Degree degNeg180 = Degree(-180.f);
        	
            SECTION("Is equal")
            {
                Radian radPi = Radian(glm::radians(180.f));

                CHECK(deg180 == radPi);
                CHECK(radPi == deg180);
                CHECK_FALSE(deg180 == degNeg180);
                CHECK_FALSE(degNeg180 == deg180);

                Radian radNegPi = Radian(glm::radians(-180.f));

                CHECK(degNeg180 == radNegPi);
                CHECK(radNegPi == degNeg180);
                CHECK_FALSE(deg180 == degNeg180);
                CHECK_FALSE(degNeg180 == deg180);
            }

            SECTION("Is not equal")
            {
                Radian radPi5 = Radian(glm::radians(36.f));
                Radian radPi5_two = Radian(glm::radians(36.f));

                CHECK(deg180 != radPi5);
                CHECK(radPi5 != deg180);
                CHECK_FALSE(radPi5 != radPi5_two);
                CHECK_FALSE(radPi5_two != radPi5);

                Radian radNegPi5 = Radian(-glm::radians(-36.f));
                Radian radNegPi5_two = Radian(-glm::radians(-36.f));

                CHECK(deg180 != radNegPi5);
                CHECK(radNegPi5 != deg180);
                CHECK_FALSE(radNegPi5 != radNegPi5_two);
                CHECK_FALSE(radNegPi5_two != radNegPi5);

                CHECK(degNeg180 != radPi5);
                CHECK(radPi5 != degNeg180);
            }
        }
    }


    TEST_CASE("Angle algebric operation", "[angle]")
    {
        SECTION("Degree")
        {
            Degree deg270 = Degree(270.f);
            Degree deg180 = Degree(180.f);
            Degree deg90 = Degree(90.f);
            Degree result;
        	
            Radian rad((float)M_PI);
        	
        	SECTION("Addition")
        	{
                result = deg180 + deg90;
        		
                CHECK(result.data == 180.f + 90.f);
        		      		
                result += rad;
        		
                CHECK(result.data == 180.f + 90.f + 180.f);

                deg270 += deg90;
        		
                CHECK(deg270.data == 270.f + 90.f);
        	}

        	SECTION("Subtraction")
        	{
                result = deg180 - deg90;

                CHECK(result.data == 180.f - 90.f);
        		
                result -= rad;

                CHECK(result.data == 180.f - 90.f - 180.f);

                deg270 -= deg90;

                CHECK(deg270.data == 270.f - 90.f);
        	}

        	SECTION("Multiplication")
        	{
                result = deg180 * 2.f;

                CHECK(result.data == 180.f * 2.f);

                result = 2.f * deg180;

                CHECK(result.data == 2.f * 180.f);	

                deg270 *= 2.f;

                CHECK(deg270.data == 270.f * 2.f);
        	}

        	SECTION("Division")
        	{
                result = deg180 / 2.f;

                CHECK(result.data == 180.f / 2.f);;

                deg270 /= 2.f;

                CHECK(deg270.data == 270.f / 2.f);
        	}
        }

    	SECTION("Radian")
        {
        	Radian radPi2 = Radian(glm::radians(90.f));
            Radian radPi4 = Radian(glm::radians(45.f));
            Radian radPi6 = Radian(glm::radians(30.f));        	
            Radian result;

            Degree deg = Degree(180.f);

            SECTION("Addition")
            {
                result = radPi4 + radPi6;

                CHECK(result.data == Approx(glm::radians(45.f + 30.f)).margin(0.00001f));

                result += deg;

                CHECK(result.data == Approx(glm::radians(45.f + 30.f + 180.f)).margin(0.00001f));

                radPi2 += radPi6;

                CHECK(radPi2.data == Approx(glm::radians(90.f + 30.f)).margin(0.00001f));
            }

            SECTION("Subtraction")
            {
                result = radPi4 - radPi6;

                CHECK(result.data == Approx(glm::radians(45.f - 30.f)).margin(0.00001f));

                result -= deg;

                CHECK(result.data == Approx(glm::radians(45.f - 30.f - 180.f)).margin(0.00001f));

                radPi2 -= radPi6;

                CHECK(radPi2.data == Approx(glm::radians(90.f - 30.f)).margin(0.00001f));
            }

            SECTION("Multiplication")
            {
                result = radPi4 * 2.f;

                CHECK(result.data == Approx(glm::radians(45.f) * 2.f).margin(0.00001f));

                result = 2.f * radPi4;

                CHECK(result.data == Approx(2.f * glm::radians(45.f)).margin(0.00001f));

                radPi2 *= 2.f;

                CHECK(radPi2.data == Approx(glm::radians(90.f) * 2.f).margin(0.00001f));
            }

            SECTION("Division")
            {
                result = radPi4 / 2.f;

                CHECK(result.data == Approx(glm::radians(45.f) / 2.f).margin(0.00001f));

                radPi2 /= 2.f;

                CHECK(result.data == Approx(glm::radians(45.f) / 2.f).margin(0.00001f));
            }
        }
    }


    TEST_CASE("Trigonometry operation", "[angle]")
    {
        Degree deg = Degree(5.f);
        Radian rad = Radian(5.f);

    	SECTION("Cos")
        {
            CHECK(cos(deg) == Approx(std::cosf(5.f * (float)M_PI / 180.f)).margin(0.00001f));
            CHECK(cos(rad) == Approx(std::cosf(5.f)).margin(0.00001f));
        }

        SECTION("Sin")
        {
            CHECK(sin(deg) == Approx(std::sinf(5.f * (float)M_PI / 180.f)).margin(0.00001f));
            CHECK(sin(rad) == Approx(std::sinf(5.f)).margin(0.00001f));
        }

    	SECTION("Tan")
        {
            CHECK(tan(deg) == Approx(std::tanf(5.f * (float)M_PI / 180.f)).margin(0.00001f));
            CHECK(tan(rad) == Approx(std::tanf(5.f)).margin(0.00001f));
        }

    	SECTION("Arc")
        {
            CHECK(acos(.5f).data == Approx(std::acosf(.5f)).margin(0.00001f));
            CHECK(asin(.5f).data == Approx(std::asinf(.5f)).margin(0.00001f));
            CHECK(atan(.5f).data == Approx(std::atanf(.5f)).margin(0.00001f));
            CHECK(atan2(.5f, .3f).data == Approx(std::atan2f(.5f, .3f)).margin(0.00001f));
        }
    }
}