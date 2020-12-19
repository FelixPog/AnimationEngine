#include "Vector/Vector2.h"

#include <catch2/catch.hpp>
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/detail/setup.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp >

namespace LibMath
{
    TEST_CASE("Vector2 Contructor", "[vector][vector2]")
    {
        SECTION("Default Contructor")
        {
            Vector2 testSubject;
        	
            REQUIRE((testSubject.x == 0.f && testSubject.y == 0.f));
            //CHECK(0 == 0);
        }
        SECTION("Param Contructor")
        {
            Vector2 testSubject(1,2);

            REQUIRE((testSubject.x == 1.f && testSubject.y == 2.f));
            //CHECK(0 == 0);
        }
        SECTION("Copy Contructor")
        {
            Vector2 testSubject(1, 2);
            Vector2 testcpy(testSubject);

            REQUIRE((testcpy.x == 1.f && testcpy.y == 2.f));
            //CHECK(0 == 0);
        }

    }

    TEST_CASE("Vector2 comparaison", "[vector][vector2][operator]")
    {
        SECTION("Comparaison Operators")
        {
            Vector2 first(4.f, 1.f);
            Vector2 second(1.f,1.f);
            bool result = first == second;
            REQUIRE(result == false);
        	
            result = first != second;
            REQUIRE(result == true);
        	
            //CHECK(0 == 0);
        }
    }

    TEST_CASE("Vector2 vector operation", "[vector][vector2]")
    {
        SECTION("Operators")
        {
            Vector2 first(4.f, 1.f);
            Vector2 second(1.f, 1.f);
            first = second;
            REQUIRE((first.x == 1 && first.y == 1));

            first += second;
            REQUIRE((first.x == 2 && first.y == 2));

            first -= second;
            REQUIRE((first.x == 1 && first.y == 1));

            first *= 4;
            REQUIRE((first.x == 4 && first.y == 4));

            first /= 2;
            REQUIRE((first.x == 2 && first.y == 2));
        	
            first = first + second;
            REQUIRE((first.x == 3 && first.y == 3));
        	
            first = first - second;
            REQUIRE((first.x == 2 && first.y == 2));

            first = first * 2;
            REQUIRE((first.x == 4 && first.y == 4));
            first = 2 * first;
            REQUIRE((first.x == 8 && first.y == 8));
        	
            first = first / 2;
            REQUIRE((first.x ==4  && first.y == 4));
        	//CHECK(0 == 0);
        }
    }
	
    TEST_CASE("Vector2 named vector", "[vector][vector2][named]")
    {
        CHECK(Vector2::Zero() == Vector2(0.f, 0.f));
        CHECK(Vector2::One() == Vector2(1.f, 1.f));
        CHECK(Vector2::Up() == Vector2(0.f, 1.f));
        CHECK(Vector2::Down() == Vector2(0.f, -1.f));
        CHECK(Vector2::Right() == Vector2(1.f, 0.f));
        CHECK(Vector2::Left() == Vector2(-1.f, 0.f));
    }
	
    TEST_CASE("Vector2 algebric operation", "[vector][vector2][operator]")
    {
        SECTION("Dot")
        {
            Vector2 first(4.f, 1.f);
            glm::vec2 first_glm(4.f, 1.f);
            Vector2 second(2.f, 4.f);
            glm::vec2 second_glm(2.f, 4.f);
        	
            float result = first.Dot(second);
            REQUIRE(result == glm::dot(first_glm, second_glm));
           // CHECK(0 == 0);
        }
    	
        SECTION("Magnitude")
        {
            Vector2 first(4, 3);
        	glm::vec2 first_glm(4.f, 3.f);
            float result = first.Magnitude();
            REQUIRE(result == glm::length(first_glm));
        }
    	
        SECTION("SquareMagnitude")
        {
            Vector2 first(4, 3);
            float result = first.SquareMagnitude();
            REQUIRE(result == 25);
        }

        SECTION("Normalize")
        {
            Vector2 first(4, 3);
            glm::vec2 first_glm(4.f, 3.f);
			first.Normalize();
            glm::vec2 norm = glm::normalize(first_glm);
            REQUIRE((first.x == norm.x && first.y == norm.y));
        }

        SECTION("AngleBetWeen two vectors")
        {
            Vector2 first(3, 4);
            Vector2 second(4, 3);
            glm::vec2 first_glm(3.f, 4.f);
            glm::vec2 second_glm(4.f, 3.f);
            Radian rad = first.ExtractAngleBetween(first, second);
            REQUIRE(rad.data == glm::angle(glm::normalize(first_glm), glm::normalize(second_glm)));
        }
    	
        SECTION("AngleBetWeen two Unit vectors")
        {
            Vector2 first(1, 0.5f);
            Vector2 second(0.1f, 0.2f);
            glm::vec2 first_glm(1.f, 0.5f);
            glm::vec2 second_glm(0.1f, 0.2f);
            Radian rad = first.GetAngleBetweenUnitVector(first, second);
          
            REQUIRE(rad.data == glm::angle(first_glm, second_glm));
        }
    }
}