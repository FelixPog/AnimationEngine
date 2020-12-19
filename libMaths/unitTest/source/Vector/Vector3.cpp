#include "Vector/Vector3.h"

#include <iostream>

#include <catch2/catch.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/detail/setup.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp >

#include "Vector/Vector4.h"

namespace LibMath
{
    namespace testVector3
    {
        float precision = 0.0000005f;
        // 0.0000002f is the smallest value you can subtract from one and not getting back one
        void NearlyEqual(Vector3 const& lhs, glm::vec3 const& rhs)
        {
            CHECK(lhs.x == Approx(rhs.x));
            CHECK(lhs.y == Approx(rhs.y));
            CHECK(lhs.z == Approx(rhs.z));
        }
        void NearlyEqual(glm::vec3 const& lhs, Vector3 const& rhs)
        {
            CHECK(Approx(lhs.x) == rhs.x);
            CHECK(Approx(lhs.y) == rhs.y);
            CHECK(Approx(lhs.z) == rhs.z);
        }
        void Equal(Vector3 const& lhs, glm::vec3 const& rhs)
        {
            CHECK(lhs.x == rhs.x);
            CHECK(lhs.y == rhs.y);
            CHECK(lhs.z == rhs.z);
        }
        void Equal(glm::vec3 const& lhs, Vector3 const& rhs)
        {
            CHECK(lhs.x == rhs.x);
            CHECK(lhs.y == rhs.y);
            CHECK(lhs.z == rhs.z);
        }
    }


    TEST_CASE("Vector3 constructor", "[vector][vector3]")
    {
        SECTION("default")
        {
            Vector3 vec;

            CHECK(vec.x == 0.f);
            CHECK(vec.y == 0.f);
            CHECK(vec.z == 0.f);
        }

        SECTION("param")
        {
            Vector3 vec(2.f, 4.f, 3.f);
            Vector3 vec2(-2.f);

            SECTION("")
            {
                CHECK(vec.x == 2.f);
                CHECK(vec.y == 4.f);
                CHECK(vec.z == 3.f);

                CHECK(vec2.x == -2.f);
                CHECK(vec2.y == -2.f);
                CHECK(vec2.z == -2.f);
            }

            SECTION("copy")
            {
                Vector3 copy(vec);

                CHECK(copy.x == 2.f);
                CHECK(copy.y == 4.f);
                CHECK(copy.z == 3.f);
            }

            SECTION("assigment")
            {
                Vector3 copy;
                copy = vec;

                CHECK(copy.x == 2.f);
                CHECK(copy.y == 4.f);
                CHECK(copy.z == 3.f);
            }
        }
    }


    TEST_CASE("Vector3 component", "[vector][vector3][operator]")
    {
        Vector3 vec(1.f, 3.f, 2.f);

        SECTION("array subscript operator")
        {
            vec.x = 5.f;
            vec.y = 6.f;
            vec.z = 4.f;

            CHECK(vec.x == 5.f);
            CHECK(vec.y == 6.f);
            CHECK(vec.z == 4.f);
        }

        SECTION("array subscript operator")
        {
            CHECK(vec[0] == vec.x);
            CHECK(vec[1] == vec.y);
            CHECK(vec[2] == vec.z);

            vec[0] = 5.f;
            vec[1] = 6.f;
            vec[2] = 4.f;

            CHECK(vec[0] == vec.x);
            CHECK(vec[1] == vec.y);
            CHECK(vec[2] == vec.z);
        }
    }


    TEST_CASE("Vector3 comparaison", "[vector][vector3][operator]")
    {
        Vector3 first(1.f, 3.f, 2.f);
        Vector3 copy = first;
        Vector3 clone(1.f, 3.f, 2.f);

        Vector3 second(4.f, 1.f, 5.f);
        Vector3 third(4.f, -3.f, 0.f);

        Vector3 fourth(5.f, 3.f, 2.f); // one different with first
        Vector3 fifth(1.f, 2.f, 2.f); // one different with first
        Vector3 sixth(1.f, 3.f, -2.f); // one different with first
        Vector3 seventh(1.f, -1.f, 0.f); // one same with first
        Vector3 eigth(2.f, 3.f, 1.f); // one same with first
        Vector3 ninth(4.f, 4.f, 2.f); // one same with first

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
            }
        }
    }


    TEST_CASE("Vector3 named vector", "[vector][vector3][named]")
    {
        CHECK(Vector3::Zero == Vector3(0.f, 0.f, 0.f));
        CHECK(Vector3::One == Vector3(1.f, 1.f, 1.f));
        CHECK(Vector3::Right == Vector3(1.f, 0.f, 0.f));
        CHECK(Vector3::Left == Vector3(-1.f, 0.f, 0.f));
        CHECK(Vector3::Up == Vector3(0.f, 1.f, 0.f));
        CHECK(Vector3::Down == Vector3(0.f, -1.f, 0.f));
        CHECK(Vector3::Front == Vector3(0.f, 0.f, 1.f));
        CHECK(Vector3::Back == Vector3(0.f, 0.f, -1.f));
    }
    

    TEST_CASE("Vector3 converion", "[vector][vector3][vector4][operator][glm]")
    {
        Vector4 vec4(2.f, 4.f, 3.f, 1.f);
        Vector4 wx(2.f, 4.f, 3.f, 1 / 3.f);
        Vector4 w0(2.f, 4.f, 3.f, 0.f);

        glm::vec4 vec4_glm(2.f, 4.f, 3.f, 1.f);
        glm::vec4 wx_glm(2.f, 4.f, 3.f, 1 / 3.f);
        glm::vec4 w0_glm(2.f, 4.f, 3.f, 0.f);

        SECTION("copy")
        {
            Vector3 copy4(vec4);
            Vector3 copy4_wx(wx);
            Vector3 copy4_w0(w0);

            glm::vec3 copy4_glm(vec4_glm);
            glm::vec3 copy4_wx_glm(wx_glm);
            glm::vec3 copy4_w0_glm(w0_glm);

            testVector3::Equal(copy4, copy4_glm);
            testVector3::Equal(copy4_w0, copy4_w0_glm);
            testVector3::Equal(copy4_wx, copy4_wx_glm);
        }

        SECTION("assigment")
        {
            Vector3 copy;
            copy = vec4;
            Vector3 copy_wx;
            copy_wx = wx;
            Vector3 copy_w0;
            copy_w0 = w0;

            glm::vec3 copy_glm;
            copy_glm = vec4_glm;
            glm::vec3 copy_wx_glm;
            copy_wx_glm = wx_glm;
            glm::vec3 copy_w0_glm;
            copy_w0_glm = w0_glm;

            testVector3::Equal(copy, copy_glm);
            testVector3::Equal(copy_wx, copy_wx_glm);
            testVector3::Equal(copy_w0, copy_w0_glm);
        }
    }


    TEST_CASE("Vector3 arithmetic operation", "[vector][vector3][operator][glm]")
    {
        Vector3 first(1.f, 3.f, 2.f);
        Vector3 second(4.f, 1.f, 5.f);
        Vector3 third(4.f, -3.f, 0.f);

        glm::vec3 first_glm(1.f, 3.f, 2.f);
        glm::vec3 second_glm(4.f, 1.f, 5.f);
        glm::vec3 third_glm(4.f, -3.f, 0.f);

        SECTION("plus (+)")
        {
            testVector3::Equal(first + 2.f, first_glm + 2.f);
            testVector3::Equal(first + 0.f, first_glm + 0.f);
            testVector3::Equal(2.f + first, 2.f + first_glm);
            testVector3::Equal(first + second, first_glm + second_glm);

            first += third;
            first_glm += third_glm;
            testVector3::Equal(first, first_glm);

            second += 3.f;
            second_glm += 3.f;
            testVector3::Equal(second, second_glm);
        }

        SECTION("minus (-)")
        {
            testVector3::Equal(-first, -first_glm);
            testVector3::Equal(first - 2.f, first_glm - 2.f);
            testVector3::Equal(first - 0.f, first_glm - 0.f);
            testVector3::Equal(2.f - first, 2.f - first_glm);
            testVector3::Equal(first - second, first_glm - second_glm);

            first -= third;
            first_glm -= third_glm;
            testVector3::Equal(first, first_glm);

            second -= 3.f;
            second_glm -= 3.f;
            testVector3::Equal(second, second_glm);
        }

        SECTION("multiply (*)")
        {
            testVector3::Equal(first * 2.f, first_glm * 2.f);
            testVector3::Equal(first * 0.f, first_glm * 0.f);
            testVector3::Equal(2.f * first, 2.f * first_glm);
            testVector3::Equal(first * second, first_glm * second_glm);

            first *= third;
            first_glm *= third_glm;
            testVector3::Equal(first, first_glm);

            second *= 3.f;
            second_glm *= 3.f;
            testVector3::Equal(second, second_glm);
        }

        SECTION("divide (/)")
        {
            testVector3::Equal(first / 2.f, first_glm / 2.f);
            testVector3::Equal(first / 0.f, first_glm / 0.f);
            testVector3::Equal(2.f / first, 2.f / first_glm);
            testVector3::Equal(first / second, first_glm / second_glm);

            first /= third;
            first_glm /= third_glm;
            testVector3::Equal(first, first_glm);

            second /= 3.f;
            second_glm /= 3.f;
            testVector3::Equal(second, second_glm);
        }
    }


    TEST_CASE("Vector3 vector operation", "[vector][vector3][glm]")
    {
        Vector3 first(1.f, 3.f, 2.f);
        Vector3 clone(1.f, 3.f, 2.f);
        Vector3 copy = first;
        Vector3 second(4.f, 1.f, 5.f);
        Vector3 third(4.f, -3.f, 0.f);

        glm::vec3 first_glm(1.f, 3.f, 2.f);
        glm::vec3 second_glm(4.f, 1.f, 5.f);
        glm::vec3 third_glm(4.f, -3.f, 0.f);

        SECTION("standard operation")
        {
            testVector3::Equal(first.Cross(first), glm::cross(first_glm, first_glm));
            testVector3::Equal(first.Cross(second), glm::cross(first_glm, second_glm));
            testVector3::Equal(first.Cross(third), glm::cross(first_glm, third_glm));
            testVector3::Equal(second.Cross(first), glm::cross(second_glm, first_glm));
            testVector3::Equal(third.Cross(first), glm::cross(third_glm, first_glm));
            testVector3::Equal(Vector3::Cross(first, first), glm::cross(first_glm, first_glm));
            testVector3::Equal(Vector3::Cross(first, second), glm::cross(first_glm, second_glm));
            testVector3::Equal(Vector3::Cross(first, third), glm::cross(first_glm, third_glm));
            testVector3::Equal(Vector3::Cross(second, first), glm::cross(second_glm, first_glm));
            testVector3::Equal(Vector3::Cross(third, first), glm::cross(third_glm, first_glm));

            CHECK(first.Dot(first) == glm::dot(first_glm, first_glm));
            CHECK(first.Dot(second) == glm::dot(first_glm, second_glm));
            CHECK(first.Dot(third) == glm::dot(first_glm, third_glm));
            CHECK(second.Dot(first) == glm::dot(second_glm, first_glm));
            CHECK(third.Dot(first) == glm::dot(third_glm, first_glm));
            CHECK(Vector3::Dot(first, first) == glm::dot(first_glm, first_glm));
            CHECK(Vector3::Dot(first, second) == glm::dot(first_glm, second_glm));
            CHECK(Vector3::Dot(first, third) == glm::dot(first_glm, third_glm));
            CHECK(Vector3::Dot(second, first) == glm::dot(second_glm, first_glm));
            CHECK(Vector3::Dot(third, first) == glm::dot(third_glm, first_glm));

            CHECK(first.Magnitude() == glm::length(first_glm));
            CHECK(second.Magnitude() == glm::length(second_glm));
            CHECK(third.Magnitude() == glm::length(third_glm));
            CHECK(Vector3::Magnitude(first) == glm::length(first_glm));
            CHECK(Vector3::Magnitude(second) == glm::length(second_glm));
            CHECK(Vector3::Magnitude(third) == glm::length(third_glm));

            CHECK(first.SquareMagnitude() == glm::length2(first_glm));
            CHECK(second.SquareMagnitude() == glm::length2(second_glm));
            CHECK(third.SquareMagnitude() == glm::length2(third_glm));
            CHECK(Vector3::SquareMagnitude(first) == glm::length2(first_glm));
            CHECK(Vector3::SquareMagnitude(second) == glm::length2(second_glm));
            CHECK(Vector3::SquareMagnitude(third) == glm::length2(third_glm));
        }

        SECTION("magnitude")
        {
            Vector3 equal(13, 84, 85);
            Vector3 equal2(36, 77, 85);

            SECTION("magnitude")
            {
                CHECK(first.Magnitude() == glm::length(first_glm));
                CHECK(second.Magnitude() == glm::length(second_glm));
                CHECK(third.Magnitude() == glm::length(third_glm));
                CHECK(Vector3::Magnitude(first) == glm::length(first_glm));
                CHECK(Vector3::Magnitude(second) == glm::length(second_glm));
                CHECK(Vector3::Magnitude(third) == glm::length(third_glm));

                CHECK(first.SquareMagnitude() == glm::length2(first_glm));
                CHECK(second.SquareMagnitude() == glm::length2(second_glm));
                CHECK(third.SquareMagnitude() == glm::length2(third_glm));
                CHECK(Vector3::SquareMagnitude(first) == glm::length2(first_glm));
                CHECK(Vector3::SquareMagnitude(second) == glm::length2(second_glm));
                CHECK(Vector3::SquareMagnitude(third) == glm::length2(third_glm));
            }

            SECTION("shorter")
            {
                CHECK(first.IsShorterThan(second));
                CHECK(first.IsShorterThan(third));
                CHECK_FALSE(second.IsShorterThan(first));
                CHECK_FALSE(second.IsShorterThan(third));
                CHECK_FALSE(third.IsShorterThan(first));
                CHECK(third.IsShorterThan(second));
                CHECK_FALSE(first.IsShorterThan(first));
                CHECK_FALSE(first.IsShorterThan(copy));
                CHECK_FALSE(first.IsShorterThan(clone));
                CHECK_FALSE(equal.IsShorterThan(equal2));
            }

            SECTION("longer")
            {
                CHECK_FALSE(first.IsLongerThan(second));
                CHECK_FALSE(first.IsLongerThan(third));
                CHECK(second.IsLongerThan(first));
                CHECK(second.IsLongerThan(third));
                CHECK(third.IsLongerThan(first));
                CHECK_FALSE(third.IsLongerThan(second));
                CHECK_FALSE(first.IsLongerThan(first));
                CHECK_FALSE(first.IsLongerThan(copy));
                CHECK_FALSE(first.IsLongerThan(clone));
                CHECK_FALSE(equal.IsLongerThan(equal2));
            }

            SECTION("shorter or equal")
            {
                CHECK(first.IsShorterOrEqualTo(second));
                CHECK(first.IsShorterOrEqualTo(third));
                CHECK_FALSE(second.IsShorterOrEqualTo(first));
                CHECK_FALSE(second.IsShorterOrEqualTo(third));
                CHECK_FALSE(third.IsShorterOrEqualTo(first));
                CHECK(third.IsShorterOrEqualTo(second));
                CHECK(first.IsShorterOrEqualTo(first));
                CHECK(first.IsShorterOrEqualTo(copy));
                CHECK(first.IsShorterOrEqualTo(clone));
                CHECK(equal.IsShorterOrEqualTo(equal2));
            }

            SECTION("longer or equal")
            {
                CHECK_FALSE(first.IsLongerOrEqualTo(second));
                CHECK_FALSE(first.IsLongerOrEqualTo(third));
                CHECK(second.IsLongerOrEqualTo(first));
                CHECK(second.IsLongerOrEqualTo(third));
                CHECK(third.IsLongerOrEqualTo(first));
                CHECK_FALSE(third.IsLongerOrEqualTo(second));
                CHECK(first.IsLongerOrEqualTo(first));
                CHECK(first.IsLongerOrEqualTo(copy));
                CHECK(first.IsLongerOrEqualTo(clone));
                CHECK(equal.IsLongerOrEqualTo(equal2));
            }

            SECTION("normalize")
            {
                CHECK_FALSE(first.IsNormalize());
                CHECK_FALSE(second.IsNormalize());
                CHECK_FALSE(third.IsNormalize());

                testVector3::NearlyEqual(first.GetNormalize(), glm::normalize(first_glm));
                testVector3::NearlyEqual(second.GetNormalize(), glm::normalize(second_glm));
                testVector3::NearlyEqual(third.GetNormalize(), glm::normalize(third_glm));

                CHECK_FALSE(first.IsNormalize());
                CHECK_FALSE(second.IsNormalize());
                CHECK_FALSE(third.IsNormalize());

                testVector3::NearlyEqual(Vector3::Normalize(first), glm::normalize(first_glm));
                testVector3::NearlyEqual(Vector3::Normalize(second), glm::normalize(second_glm));
                testVector3::NearlyEqual(Vector3::Normalize(third), glm::normalize(third_glm));

                CHECK_FALSE(first.IsNormalize());
                CHECK_FALSE(second.IsNormalize());
                CHECK_FALSE(third.IsNormalize());

                first.Normalize();
                second.Normalize();
                third.Normalize();

                testVector3::NearlyEqual(first, glm::normalize(first_glm));
                testVector3::NearlyEqual(second, glm::normalize(second_glm));
                testVector3::NearlyEqual(third, glm::normalize(third_glm));

                CHECK(first.IsNormalize());
                CHECK(second.IsNormalize());
                CHECK(third.IsNormalize());
            }
        }

        SECTION("distance")
        {
            CHECK(first.DistanceTo(first) == glm::distance(first_glm, first_glm));
            CHECK(first.DistanceTo(second) == glm::distance(first_glm, second_glm));
            CHECK(first.DistanceTo(third) == glm::distance(first_glm, third_glm));
            CHECK(second.DistanceTo(first) == glm::distance(second_glm, first_glm));
            CHECK(second.DistanceTo(third) == glm::distance(second_glm, third_glm));
            CHECK(third.DistanceTo(first) == glm::distance(third_glm, first_glm));
            CHECK(third.DistanceTo(second) == glm::distance(third_glm, second_glm));

            CHECK(Vector3::DistanceBetween(first, first) == glm::distance(first_glm, first_glm));
            CHECK(Vector3::DistanceBetween(first, second) == glm::distance(first_glm, second_glm));
            CHECK(Vector3::DistanceBetween(first, third) == glm::distance(first_glm, third_glm));
            CHECK(Vector3::DistanceBetween(second, first) == glm::distance(second_glm, first_glm));
            CHECK(Vector3::DistanceBetween(second, third) == glm::distance(second_glm, third_glm));
            CHECK(Vector3::DistanceBetween(third, first) == glm::distance(third_glm, first_glm));
            CHECK(Vector3::DistanceBetween(third, second) == glm::distance(third_glm, second_glm));
        }

        SECTION("angle")
        {
            CHECK(first.AngleTo(first).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(first_glm)));
            CHECK(first.AngleTo(second).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(second_glm)));
            CHECK(first.AngleTo(third).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(third_glm)));
            CHECK(second.AngleTo(first).rad() == glm::angle(glm::normalize(second_glm), glm::normalize(first_glm)));
            CHECK(second.AngleTo(third).rad() == glm::angle(glm::normalize(second_glm), glm::normalize(third_glm)));
            CHECK(third.AngleTo(first).rad() == glm::angle(glm::normalize(third_glm), glm::normalize(first_glm)));
            CHECK(third.AngleTo(second).rad() == glm::angle(glm::normalize(third_glm), glm::normalize(second_glm)));

            CHECK(Vector3::AngleBetween(first, first).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(first_glm)));
            CHECK(Vector3::AngleBetween(first, second).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(second_glm)));
            CHECK(Vector3::AngleBetween(first, third).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(third_glm)));
            CHECK(Vector3::AngleBetween(second, first).rad() == glm::angle(glm::normalize(second_glm), glm::normalize(first_glm)));
            CHECK(Vector3::AngleBetween(second, third).rad() == glm::angle(glm::normalize(second_glm), glm::normalize(third_glm)));
            CHECK(Vector3::AngleBetween(third, first).rad() == glm::angle(glm::normalize(third_glm), glm::normalize(first_glm)));
            CHECK(Vector3::AngleBetween(third, second).rad() == glm::angle(glm::normalize(third_glm), glm::normalize(second_glm)));

            glm::vec3 first2_glm(1.f, 0.f, 2.f);
            glm::vec3 second2_glm(4.f, 0.f, 5.f);
            glm::vec3 third2_glm(4.f, 0.f, 0.f);

            CHECK(first.TopDownAngleTo(first).rad() == glm::orientedAngle(glm::normalize(first2_glm), glm::normalize(first2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(first.TopDownAngleTo(second).rad() == glm::orientedAngle(glm::normalize(first2_glm), glm::normalize(second2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(first.TopDownAngleTo(third).rad() == glm::orientedAngle(glm::normalize(first2_glm), glm::normalize(third2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(second.TopDownAngleTo(first).rad() == glm::orientedAngle(glm::normalize(second2_glm), glm::normalize(first2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(second.TopDownAngleTo(third).rad() == glm::orientedAngle(glm::normalize(second2_glm), glm::normalize(third2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(third.TopDownAngleTo(first).rad() == glm::orientedAngle(glm::normalize(third2_glm), glm::normalize(first2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(third.TopDownAngleTo(second).rad() == glm::orientedAngle(glm::normalize(third2_glm), glm::normalize(second2_glm), glm::vec3(0.f, 1.f, 0.f)));

            CHECK(Vector3::TopDownAngleBetween(first, first).rad() == glm::orientedAngle(glm::normalize(first2_glm), glm::normalize(first2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(Vector3::TopDownAngleBetween(first, second).rad() == glm::orientedAngle(glm::normalize(first2_glm), glm::normalize(second2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(Vector3::TopDownAngleBetween(first, third).rad() == glm::orientedAngle(glm::normalize(first2_glm), glm::normalize(third2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(Vector3::TopDownAngleBetween(second, first).rad() == glm::orientedAngle(glm::normalize(second2_glm), glm::normalize(first2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(Vector3::TopDownAngleBetween(second, third).rad() == glm::orientedAngle(glm::normalize(second2_glm), glm::normalize(third2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(Vector3::TopDownAngleBetween(third, first).rad() == glm::orientedAngle(glm::normalize(third2_glm), glm::normalize(first2_glm), glm::vec3(0.f, 1.f, 0.f)));
            CHECK(Vector3::TopDownAngleBetween(third, second).rad() == glm::orientedAngle(glm::normalize(third2_glm), glm::normalize(second2_glm), glm::vec3(0.f, 1.f, 0.f)));

            first.Normalize();
            second.Normalize();
            third.Normalize();

            CHECK(Vector3::GetAngleBetweenUnitVector(first, first).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(first_glm)));
            CHECK(Vector3::GetAngleBetweenUnitVector(first, second).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(second_glm)));
            CHECK(Vector3::GetAngleBetweenUnitVector(first, third).rad() == glm::angle(glm::normalize(first_glm), glm::normalize(third_glm)));
            CHECK(Vector3::GetAngleBetweenUnitVector(second, first).rad() == glm::angle(glm::normalize(second_glm), glm::normalize(first_glm)));
            CHECK(Vector3::GetAngleBetweenUnitVector(second, third).rad() == glm::angle(glm::normalize(second_glm), glm::normalize(third_glm)));
            CHECK(Vector3::GetAngleBetweenUnitVector(third, first).rad() == glm::angle(glm::normalize(third_glm), glm::normalize(first_glm)));
            CHECK(Vector3::GetAngleBetweenUnitVector(third, second).rad() == glm::angle(glm::normalize(third_glm), glm::normalize(second_glm)));
        }
    }

}