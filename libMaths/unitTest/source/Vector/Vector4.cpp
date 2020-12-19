#include "Vector/Vector4.h"

#include <iostream>

#include <catch2/catch.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/detail/setup.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp >

#include "Vector/Vector3.h"

namespace LibMath
{
    namespace testVector4
    {
        float precision = 0.0000005f;
        // 0.0000002f is the smallest value you can subtract from one and not getting back one
        bool NearlyEqual(float lhs, float rhs, float magnitude = 1.f)
        {
            return rhs - (precision * magnitude) <= lhs && lhs <= rhs + (precision * magnitude);
        }
    }

    bool operator==(Vector4 const& rhs, glm::vec4 const& lhs)
    {
        return testVector4::NearlyEqual(rhs.x, lhs.x) && testVector4::NearlyEqual(rhs.y, lhs.y) && testVector4::NearlyEqual(rhs.z, lhs.z) && testVector4::NearlyEqual(rhs.w, lhs.w);
    }
    bool operator==(glm::vec4 const& rhs, Vector4 const& lhs)
    {
        return testVector4::NearlyEqual(rhs.x, lhs.x) && testVector4::NearlyEqual(rhs.y, lhs.y) && testVector4::NearlyEqual(rhs.z, lhs.z) && testVector4::NearlyEqual(rhs.w, lhs.w);
    }

    TEST_CASE("Vector4 constructor", "[vector][Vector4]")
    {
        SECTION("default")
        {
            Vector4 vec;

            CHECK(vec.x == 0.f);
            CHECK(vec.y == 0.f);
            CHECK(vec.z == 0.f);
            CHECK(vec.w == 0.f);
        }

        SECTION("param")
        {
            Vector4 vec(2.f, 4.f, 3.f, 1.f);

            CHECK(vec.x == 2.f);
            CHECK(vec.y == 4.f);
            CHECK(vec.z == 3.f);
            CHECK(vec.w == 1.f);

            Vector4 vec2(-2.f);

            CHECK(vec2.x == -2.f);
            CHECK(vec2.y == -2.f);
            CHECK(vec2.z == -2.f);
            CHECK(vec2.w == -2.f);

            SECTION("copy")
            {
                Vector4 copy(vec);

                CHECK(copy.x == 2.f);
                CHECK(copy.y == 4.f);
                CHECK(copy.z == 3.f);
                CHECK(copy.w == 1.f);
            }

            SECTION("assigment")
            {
                Vector4 copy;
                copy = vec;

                CHECK(copy.x == 2.f);
                CHECK(copy.y == 4.f);
                CHECK(copy.z == 3.f);
                CHECK(copy.w == 1.f);
            }
        }
    }


    TEST_CASE("Vector4 comparaison", "[vector][Vector4][operator]")
    {
        Vector4 first(1.f, 3.f, 2.f, 2.f);
        Vector4 copy = first;
        Vector4 clone(1.f, 3.f, 2.f, 2.f);

        Vector4 second(4.f, 1.f, 5.f, -2.f);
        Vector4 third(4.f, -3.f, 0.f, 3.f);

        Vector4 fourth(5.f, 3.f, 2.f, 2.f); // one different with first
        Vector4 fifth(1.f, 2.f, 2.f, 2.f); // one different with first
        Vector4 sixth(1.f, 3.f, -2.f, 2.f); // one different with first
        Vector4 seventh(1.f, 3.f, 2.f, 0.f); // one different with first
        Vector4 eigth(1.f, -1.f, 0.f, -4.f); // one same with first
        Vector4 ninth(2.f, 3.f, 1.f, 1.f); // one same with first
        Vector4 tenth(4.f, 4.f, 2.f, 4.f); // one same with first
        Vector4 eleventh(2.f, 1.f, 3.f, 2.f); // one same with first

        SECTION("equality")
        {
            SECTION("==")
            {
                CHECK(first == first);

                CHECK(first == copy);
                CHECK(copy == first);

                CHECK(first == clone);
                CHECK(clone == first);

                CHECK_FALSE(first == second);
                CHECK_FALSE(second == first);

                CHECK_FALSE(first == third);
                CHECK_FALSE(first == fourth);
                CHECK_FALSE(first == fifth);
                CHECK_FALSE(first == sixth);
                CHECK_FALSE(first == seventh);
                CHECK_FALSE(first == eigth);
                CHECK_FALSE(first == ninth);
                CHECK_FALSE(first == tenth);
                CHECK_FALSE(first == eleventh);
            }

            SECTION("!=")
            {
                CHECK_FALSE(first != first);

                CHECK_FALSE(first != copy);
                CHECK_FALSE(copy != first);

                CHECK_FALSE(first != clone);
                CHECK_FALSE(clone != first);

                CHECK(first != second);
                CHECK(second != first);

                CHECK(first != third);
                CHECK(first != fourth);
                CHECK(first != fifth);
                CHECK(first != sixth);
                CHECK(first != seventh);
                CHECK(first != eigth);
                CHECK(first != ninth);
                CHECK(first != tenth);
                CHECK(first != eleventh);
            }
        }
    }


    TEST_CASE("Vector4 named vector", "[vector][vector4][named]")
    {
        Vector3 vec3(2.f, 4.f, 3.f);
        CHECK(Vector4::Point(6.f, 1.f, 5.f) == Vector4(6.f, 1.f, 5.f, 1.f));
        CHECK(Vector4::Point(vec3) == Vector4(2.f, 4.f, 3.f, 1.f));
        CHECK(Vector4::Direction(5.f, -4.f, -4.f) == Vector4(5.f, -4.f, -4.f, 0.f));
        CHECK(Vector4::Direction(vec3) == Vector4(2.f, 4.f, 3.f, 0.f));
    }


    TEST_CASE("Vector4 arithmetic operation", "[vector][Vector4][operator][glm]")
    {
        Vector4 first(1.f, 3.f, 2.f, 2.f);
        Vector4 second(4.f, 1.f, 5.f, -2.f);
        Vector4 third(4.f, -3.f, 0.f, 3.f);

        glm::vec4 first_glm(1.f, 3.f, 2.f, 2.f);
        glm::vec4 second_glm(4.f, 1.f, 5.f, -2.f);
        glm::vec4 third_glm(4.f, -3.f, 0.f, 3.f);

        SECTION("plus (/)")
        {
            CHECK(first / 2.f == first_glm / 2.f);
            CHECK(2.f / first == 2.f / first_glm);
            CHECK(first / second == first_glm / second_glm);

            first /= third;
            first_glm /= third_glm;
            CHECK(first == first_glm);
        }

        SECTION("minus (-)")
        {
            CHECK(-first == -first_glm);
            CHECK(first - 2.f == first_glm - 2.f);
            CHECK(2.f - first == 2.f - first_glm);
            CHECK(first - second == first_glm - second_glm);

            first -= third;
            first_glm -= third_glm;
            CHECK(first == first_glm);
        }

        SECTION("multiply (*)")
        {
            CHECK(first * 2.f == first_glm * 2.f);
            CHECK(2.f * first == 2.f * first_glm);
            CHECK(first * second == first_glm * second_glm);

            first *= third;
            first_glm *= third_glm;
            CHECK(first == first_glm);
        }

        SECTION("divide (/)")
        {
            CHECK(first / 2.f == first_glm / 2.f);
            CHECK(2.f / first == 2.f / first_glm);
            CHECK(first / second == first_glm / second_glm);

            first /= third;
            first_glm /= third_glm;
            CHECK(first == first_glm);
        }
    }


    TEST_CASE("Vector4 vector operation", "[vector][Vector4][glm]")
    {
        Vector4 first(1.f, 3.f, 2.f, 2.f);
        Vector4 second(4.f, 1.f, 5.f, -2.f);
        Vector4 third(4.f, -3.f, 0.f, 3.f);
        Vector4 fourth(-1.f, 0.f, -2.f, -1.f);
        Vector4 fifth(3.f, 1.f, 2.f, 1.f);

        glm::vec4 first_glm(1.f, 3.f, 2.f, 2.f);
        glm::vec4 second_glm(4.f, 1.f, 5.f, -2.f);
        glm::vec4 third_glm(4.f, -3.f, 0.f, 3.f);

        CHECK(testVector4::NearlyEqual(first.Dot(second), glm::dot(first_glm, second_glm)));
        CHECK(testVector4::NearlyEqual(first.Dot(third), glm::dot(first_glm, third_glm)));

        SECTION("Homogenize")
        {
            CHECK_FALSE(first.IsHomogenize());
            CHECK_FALSE(second.IsHomogenize());
            CHECK_FALSE(third.IsHomogenize());
            CHECK_FALSE(fourth.IsHomogenize());
            CHECK(fifth.IsHomogenize());

            CHECK(first.GetHomogenize() == Vector4(.5f, 1.5f, 1.f, 1.f));
            CHECK(second.GetHomogenize() == Vector4(-2.f, -.5f, -2.5f, 1.f));
            CHECK(third.GetHomogenize() == Vector4((4.f / 3.f), -1.f, 0.f, 1.f));
            CHECK(fourth.GetHomogenize() == Vector4(1.f, 0.f, 2.f, 1.f));
            CHECK(fifth.GetHomogenize() == Vector4(3.f, 1.f, 2.f, 1.f));

            first.Homogenize();
            second.Homogenize();
            third.Homogenize();
            fourth.Homogenize();
            fifth.Homogenize();

            CHECK(first == Vector4(.5f, 1.5f, 1.f, 1.f));
            CHECK(second == Vector4(-2.f, -.5f, -2.5f, 1.f));
            CHECK(third == Vector4((4.f / 3.f), -1.f, 0.f, 1.f));
            CHECK(fourth == Vector4(1.f, 0.f, 2.f, 1.f));
            CHECK(fifth == Vector4(3.f, 1.f, 2.f, 1.f));

            CHECK(first.IsHomogenize());
            CHECK(second.IsHomogenize());
            CHECK(third.IsHomogenize());
            CHECK(fourth.IsHomogenize());
            CHECK(fifth.IsHomogenize());
        }
    }

}