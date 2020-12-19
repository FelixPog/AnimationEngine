#include "Random.h"

#include <catch2/catch.hpp>
#define GLM_FORCE_SILENT_WARNINGS

namespace LibMath
{
    TEST_CASE("Random Contructor", "[Random]")
    {
        SECTION("Default Contructor")
        {
            Random random;
            Random random2;
            REQUIRE(random.GetSeed() != 0);
            REQUIRE(random2.GetSeed() != 0);
            REQUIRE(random.GetSeed() != random2.GetSeed());

        }
        SECTION("Copy Constructor")
        {
            Random random;
            Random random2(random);
            REQUIRE(random.GetSeed() == random2.GetSeed());
        }
        SECTION("Param Constructor")
        {
            Random random(1332);
            REQUIRE(random.GetSeed() == 1332);
        }
    }

    TEST_CASE("Random Operator", "[Random]")
    {
        SECTION("Copy Operator")
        {
            Random random;
            Random random2;
            random = random2;
            REQUIRE(random.GetSeed() == random2.GetSeed());
        }
    }

    TEST_CASE("Random Seed functions", "[Random]")
    {
        SECTION("GetSeed Function")
        {
            Random random(1332);
            REQUIRE(random.GetSeed() == 1332);
            REQUIRE(random.GetSeed() == random.GetSeed());
        }
        SECTION("MutateSeed Param Function")
        {
            Random random;
            random.MutateSeed(1332);
            REQUIRE(random.GetSeed() == 1332);
        }
        SECTION("MutateSeed Function")
        {
            Random random(1332);
            Random random2(1333);
            random.MutateSeed();
            random2.MutateSeed();
            REQUIRE(random.GetSeed() != 1332);
            REQUIRE(random2.GetSeed() != 1333);
            REQUIRE(random.GetSeed() != random2.GetSeed());
        }
    }

    TEST_CASE("Random Int functions", "[Random]")
    {
        SECTION("RandomInt Function")
        {
            Random random;
            Random random2;

            int test1 = random.RandomInt();
            int test2 = random.RandomInt();

            int test3 = random2.RandomInt();
            int test4 = random2.RandomInt();

            REQUIRE(test1 != test2);
            REQUIRE(test3 != test4);
            REQUIRE(test1 != test3);

            REQUIRE((test1 >= 0 && test2 >= 0 && test3 >= 0 && test4 >= 0));
        }
        SECTION("RandomIntRange Function")
        {
            Random random;
            Random random2;

            int test1 = random.RandomIntInRange();
            int test2 = random2.RandomIntInRange();

            int test3 = random.RandomIntInRange(-20, 430);
            int test4 = random.RandomIntInRange(430, -20);
            int test5 = random.RandomIntInRange(30, 30);

            int test6 = random.RandomIntInRange(-50, -10);



            REQUIRE(test1 != test2);
            REQUIRE((test1 >= 0 && test2 >= 0));

            REQUIRE((test3 >= -20 && test3 <= 430));
            REQUIRE((test4 >= -20 && test4 <= 430));

            REQUIRE(test5 == 30);

            REQUIRE((test6 <= -10 && test6 >= -50));
        }
    }

    TEST_CASE("Random Float functions", "[Random]")
    {
        SECTION("RandomFloat Function")
        {
            Random random;
            Random random2;

            float test1 = random.RandomFloat();
            float test2 = random.RandomFloat();

            float test3 = random2.RandomFloat();
            float test4 = random2.RandomFloat();

            REQUIRE(test1 != test2);
            REQUIRE(test3 != test4);
            REQUIRE(test1 != test3);

            REQUIRE((test1 >= 0.f && test2 >= 0.f && test3 >= 0.f && test4 >= 0.f));
        }
        SECTION("RandomFloatRange Function")
        {
            Random random;
            Random random2;

            float test1 = random.RandomFloatInRange();
            float test2 = random2.RandomFloatInRange();

            float test3 = random.RandomFloatInRange(-20.f, 430.f);
            float test4 = random.RandomFloatInRange(430.f, -20.f);
            float test5 = random.RandomFloatInRange(30.f, 30.f);

            float test6 = random.RandomFloatInRange(-50.f, -10.f);



            REQUIRE(test1 != test2);
            REQUIRE((test1 >= 0.f && test2 >= 0.f));

            REQUIRE((test3 >= -20.f && test3 <= 430.f));
            REQUIRE((test4 >= -20.f && test4 <= 430.f));

            REQUIRE(test5 == 30.f);

            REQUIRE((test6 <= -10.f && test6 >= -50.f));
        }
    }

    TEST_CASE("Other Random functions", "[Random]")
    {
        SECTION("RandomUnitVector Function")
        {
            Random random;
            Random random2;

            Vector3 uVector1 = random.RandomUnitVector();
            Vector3 uVector2 = random.RandomUnitVector();

            Vector3 uVector3 = random2.RandomUnitVector();
            Vector3 uVector4 = random2.RandomUnitVector();

            REQUIRE((uVector1 != uVector2));
            REQUIRE((uVector3 != uVector4));
            REQUIRE((uVector1 != uVector3));

            REQUIRE((uVector1.IsNormalize() && uVector2.IsNormalize() && uVector3.IsNormalize() && uVector4.IsNormalize()));

        }
        SECTION("RandomPointInCircle Function")
        {
            Random random;
            Random random2;

            Vector3 point1 = random.RandomPointInCircle(5.f);
            Vector3 point2 = random.RandomPointInCircle(5.f);

            Vector3 point3 = random2.RandomPointInCircle(5.f);
            Vector3 point4 = random2.RandomPointInCircle(5.f);

            Vector3 point5 = random.RandomPointInCircle();
            Vector3 point6 = random.RandomPointInCircle(-1.f);

            Vector3 center{ 7.f, 12.f, 8.f };

            Vector3 point7 = random.RandomPointInCircle(0.f, center);
            Vector3 point8 = random.RandomPointInCircle(-1.f, center);



            Vector3 point9 = random.RandomPointInCircle(7.f, center);
            Vector3 point10 = random.RandomPointInCircle(7.f, center);

            REQUIRE((point1 != point2));
            REQUIRE((point3 != point4));
            REQUIRE((point1 != point3));

            REQUIRE((point5 == Vector3{ 0.f, 0.f, 0.f }));
            REQUIRE((point6 == Vector3{ 0.f, 0.f, 0.f }));
            REQUIRE((point7 == center));
            REQUIRE((point8 == center));

            REQUIRE((point9 != point10));

            REQUIRE((point1.DistanceTo({ 0.f, 0.f, 0.f })) <= 5.f);
            REQUIRE((point2.DistanceTo({ 0.f, 0.f, 0.f })) <= 5.f);
            REQUIRE((point3.DistanceTo({ 0.f, 0.f, 0.f })) <= 5.f);
            REQUIRE((point4.DistanceTo({ 0.f, 0.f, 0.f })) <= 5.f);

            REQUIRE((point5.DistanceTo({ 0.f, 0.f, 0.f })) == 0.f);
            REQUIRE((point6.DistanceTo({ 0.f, 0.f, 0.f })) == 0.f);
            REQUIRE((point7.DistanceTo(center)) == 0.f);
            REQUIRE((point8.DistanceTo(center)) == 0.f);

            REQUIRE((point9.DistanceTo(center)) <= 7.f);
            REQUIRE((point10.DistanceTo(center)) <= 7.f);
        }
    }
	
}