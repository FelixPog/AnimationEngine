#include "Matrix/Matrix4.h"
#include "Vector/Vector.h"
#include "Quaternion/Quaternion.h"

#include <catch2/catch.hpp>
#include <sstream>
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/detail/setup.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace LibMath
{
	namespace testMat4
	{
		float precision = 0.0000005f;
		// 0.0000002f is the smallest value you can subtract from one and not getting back one
		bool NearlyEqual(float lhs, float rhs, float magnitude = 1.f)
		{
			float min = rhs - (precision * magnitude);
			float max = rhs + (precision * magnitude);
			(void)min;
			(void)max;
			bool lower = min <= lhs;
			bool greater = lhs <= max;
			(void)lower;
			(void)greater;

			return rhs - (precision * magnitude) <= lhs && lhs <= rhs + (precision * magnitude);
		}

		bool operator==(Vector3 const& rhs, glm::vec3 const& lhs)
		{
			return testMat4::NearlyEqual(rhs.x, lhs.x) && testMat4::NearlyEqual(rhs.y, lhs.y) && testMat4::NearlyEqual(rhs.z, lhs.z);
		}
		bool operator==(glm::vec3 const& rhs, Vector3 const& lhs)
		{
			return testMat4::NearlyEqual(rhs.x, lhs.x) && testMat4::NearlyEqual(rhs.y, lhs.y) && testMat4::NearlyEqual(rhs.z, lhs.z);
		}
	}
	//TODO Change check test for glm comparaison
	bool operator==(Matrix4 const& rhs, glm::mat4 const& lhs)
	{
		CHECK(testMat4::NearlyEqual(rhs[0][0], lhs[0][0], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[0][1], lhs[0][1], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[0][2], lhs[0][2], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[0][3], lhs[0][3], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[1][0], lhs[1][0], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[1][1], lhs[1][1], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[1][2], lhs[1][2], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[1][3], lhs[1][3], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[2][0], lhs[2][0], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[2][1], lhs[2][1], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[2][2], lhs[2][2], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[2][3], lhs[2][3], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[3][0], lhs[3][0], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[3][1], lhs[3][1], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[3][2], lhs[3][2], 10.f));
		CHECK(testMat4::NearlyEqual(rhs[3][3], lhs[3][3], 10.f));

		return true;
	}
	bool operator==(glm::mat4 const& rhs, Matrix4 const& lhs)
	{
		return lhs == rhs;
	}

	TEST_CASE("Matrix4 ctor", "[Matrix4][Matrix44]")
	{
		SECTION("Default ctor")
		{
			Matrix4 test;

			CHECK((test[0][0] == 0.f
				&& test[0][1] == 0.f
				&& test[0][2] == 0.f
				&& test[0][3] == 0.f
				&& test[1][0] == 0.f
				&& test[1][1] == 0.f
				&& test[1][2] == 0.f
				&& test[1][3] == 0.f
				&& test[2][0] == 0.f
				&& test[2][1] == 0.f
				&& test[2][2] == 0.f
				&& test[2][3] == 0.f
				&& test[3][0] == 0.f
				&& test[3][1] == 0.f
				&& test[3][2] == 0.f
				&& test[3][3] == 0.f
				));
		}

		SECTION("Diagonal ctor")
		{
			Matrix4 test(2.f);

			REQUIRE(test[0][1] == 0);
			REQUIRE((test[0][0] == 2.f
				&& test[1][1] == 2.f
				&& test[2][2] == 2.f
				&& test[3][3] == 2.f));

			CHECK((test[0][0] == 2.f
				&& test[0][1] == 0.f
				&& test[0][2] == 0.f
				&& test[0][3] == 0.f
				&& test[1][0] == 0.f
				&& test[1][1] == 2.f
				&& test[1][2] == 0.f
				&& test[1][3] == 0.f
				&& test[2][0] == 0.f
				&& test[2][1] == 0.f
				&& test[2][2] == 2.f
				&& test[2][3] == 0.f
				&& test[3][0] == 0.f
				&& test[3][1] == 0.f
				&& test[3][2] == 0.f
				&& test[3][3] == 2.f
				));
		}

		SECTION("Quaternion ctor")
		{
			Vector3 axis = Vector3(1.f, 0.f, 0.f);
			Quaternion quat = Quaternion(Radian(2.5f), axis);
			axis = Vector3(0.f, 1.f, 0.f);
			quat *= Quaternion(Radian(-4.f), axis);
			axis = Vector3(0.f, 0.f, 1.f);
			quat *= Quaternion(Radian(1.7f), axis);
			Matrix4 test = Matrix4::Rotation(quat);


			glm::quat glmQuat = glm::quat(glm::vec3(2.5f, -4.f, 1.7f));
			glm::mat4 glmTest = glm::toMat4(glmQuat);

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 copy ctor")
		{
			Matrix4 test2(1.f);
			Matrix4 test = test2;

			REQUIRE(test[0][1] == 0);
			REQUIRE((test[0][0] == 1.f
				&& test[1][1] == 1.f
				&& test[2][2] == 1.f
				&& test[3][3] == 1.f));

			CHECK((test[0][0] == 1.f
				&& test[0][1] == 0.f
				&& test[0][2] == 0.f
				&& test[0][3] == 0.f
				&& test[1][0] == 0.f
				&& test[1][1] == 1.f
				&& test[1][2] == 0.f
				&& test[1][3] == 0.f
				&& test[2][0] == 0.f
				&& test[2][1] == 0.f
				&& test[2][2] == 1.f
				&& test[2][3] == 0.f
				&& test[3][0] == 0.f
				&& test[3][1] == 0.f
				&& test[3][2] == 0.f
				&& test[3][3] == 1.f
				));
		}

		SECTION("Matrix4 identity")
		{
			Matrix4 test = Matrix4::Identity();

			REQUIRE(test[0][1] == 0);
			REQUIRE((test[0][0] == 1.f
				&& test[1][1] == 1.f
				&& test[2][2] == 1.f
				&& test[3][3] == 1.f));

			CHECK((test[0][0] == 1.f
				&& test[0][1] == 0.f
				&& test[0][2] == 0.f
				&& test[0][3] == 0.f
				&& test[1][0] == 0.f
				&& test[1][1] == 1.f
				&& test[1][2] == 0.f
				&& test[1][3] == 0.f
				&& test[2][0] == 0.f
				&& test[2][1] == 0.f
				&& test[2][2] == 1.f
				&& test[2][3] == 0.f
				&& test[3][0] == 0.f
				&& test[3][1] == 0.f
				&& test[3][2] == 0.f
				&& test[3][3] == 1.f
				));
		}

		SECTION("Matrix4 translation")
		{
			Matrix4 test = Matrix4::Translation(2, 4, 9);
			glm::mat4 glmTest(1.f);
			glmTest = glm::translate(glmTest, { 2, 4, 9 });

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 translate")
		{
			Matrix4 test = Matrix4::Identity();
			test.Translate(2, 4, 9);
			glm::mat4 glmTest(1.f);
			glmTest = glm::translate(glmTest, { 2, 4, 9 });

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 rotation")
		{
			Matrix4 test = Matrix4::Rotation(Degree(2), Degree(4), Degree(9));
			glm::mat4 glmTest(1.f);
			glmTest = glm::rotate(glmTest, glm::radians(9.f), { 0.f, 0.f, 1.f });
			glmTest = glm::rotate(glmTest, glm::radians(2.f), { 1.f, 0.f, 0.f });
			glmTest = glm::rotate(glmTest, glm::radians(4.f), { 0.f, 1.f, 0.f });

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 rotate")
		{
			Matrix4 test = Matrix4::Identity();
			test.Rotate(Degree(2), Degree(4), Degree(9));
			glm::mat4 glmTest(1.f);
			glmTest = glm::rotate(glmTest, glm::radians(9.f), { 0.f, 0.f, 1.f });
			glmTest = glm::rotate(glmTest, glm::radians(2.f), { 1.f, 0.f, 0.f });
			glmTest = glm::rotate(glmTest, glm::radians(4.f), { 0.f, 1.f, 0.f });

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 scaling")
		{
			Matrix4 test = Matrix4::Scaling(2, 4, 9);
			glm::mat4 glmTest(1.f);
			glmTest = glm::scale(glmTest, { 2.f, 4.f, 9.f });

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 scale")
		{
			Matrix4 test = Matrix4::Identity();
			test.Scale(2, 4, 9);
			glm::mat4 glmTest(1.f);
			glmTest = glm::scale(glmTest, { 2.f, 4.f, 9.f });

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 transpose")
		{
			Matrix4 test = Matrix4::Rotation(Degree(2), Degree(4), Degree(9));
			glm::mat4 glmTest(1.f);
			glmTest = glm::rotate(glmTest, glm::radians(9.f), { 0.f, 0.f, 1.f });
			glmTest = glm::rotate(glmTest, glm::radians(2.f), { 1.f, 0.f, 0.f });
			glmTest = glm::rotate(glmTest, glm::radians(4.f), { 0.f, 1.f, 0.f });

			test.Transpose();
			glmTest = glm::transpose(glmTest);

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 LookAt")
		{
			Vector3 eye(6.f, 6.f, 7.f);
			Vector3 center(0.f, 0.f, 0.f);
			Vector3 up(0.f, 1.f, 0.f);

			Matrix4 test = Matrix4::LookAt(eye, center, up);
			glm::mat4 glmTest = glm::lookAt(glm::vec3(6, 6, 7), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

			float detTest = test.Determinant();
			float detGLM = glm::determinant(glmTest);

			CHECK(detTest == Approx(detGLM));
			CHECK(testMat4::NearlyEqual(detTest, detGLM));

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 Ortho")
		{
			float near = 0.1f;
			float far = 100.f;
			float aspectRatio = 1920.f / 1080.f;
			float r = 50.f * aspectRatio, t = 50.f;
			float l = -r, b = -t;

			Matrix4 test = Matrix4::Orthographic(l, r, b, t, near, far);
			glm::mat4 glmTest = glm::ortho(l, r, b, t, near, far);

			float detTest = test.Determinant();
			float detGLM = glm::determinant(glmTest);

			CHECK(detTest == Approx(detGLM));
			CHECK(testMat4::NearlyEqual(detTest, detGLM));
			CHECK(test == glmTest);
		}

		SECTION("Matrix4 Perspective")
		{
			float near = 0.1f;
			float far = 100.f;
			float aspectRatio = 1920.f / 1080.f;

			Matrix4 test = Matrix4::Perspective(Degree(90.f), aspectRatio, near, far);
			glm::mat4 glmTest = glm::perspective(glm::radians(90.f), aspectRatio, near, far);

			float detTest = test.Determinant();
			float detGLM = glm::determinant(glmTest);

			CHECK(detTest == Approx(detGLM));
			CHECK(testMat4::NearlyEqual(detTest, detGLM));
			CHECK(test == glmTest);
		}

		SECTION("Matrix4 determinant")
		{
			Matrix4 test = Matrix4::Rotation(Degree(6), Degree(9), Degree(7));
			glm::mat4 glmTest(1.f);
			glmTest = glm::rotate(glmTest, glm::radians(7.f), { 0.f, 0.f, 1.f });
			glmTest = glm::rotate(glmTest, glm::radians(6.f), { 1.f, 0.f, 0.f });
			glmTest = glm::rotate(glmTest, glm::radians(9.f), { 0.f, 1.f, 0.f });

			float detTest = test.Determinant();
			float detGLM = glm::determinant(glmTest);

			CHECK(detTest == Approx(detGLM));
			CHECK(testMat4::NearlyEqual(detTest, detGLM));
		}

		SECTION("Matrix4 inverse")
		{
			Matrix4 test = Matrix4::Rotation(Degree(2), Degree(4), Degree(9));
			test.Translate(2.f, 4.f, 9.f);
			test.Scale(2.f, 4.f, 9.f);

			glm::mat4 glmTest(1.f);
			glmTest = glm::scale(glmTest, { 2.f, 4.f, 9.f });
			glmTest = glm::translate(glmTest, { 2.f, 4.f, 9.f });
			glmTest = glm::rotate(glmTest, glm::radians(9.f), { 0.f, 0.f, 1.f });
			glmTest = glm::rotate(glmTest, glm::radians(2.f), { 1.f, 0.f, 0.f });
			glmTest = glm::rotate(glmTest, glm::radians(4.f), { 0.f, 1.f, 0.f });


			REQUIRE(test == glmTest);

			float detTest = test.Determinant();
			float detGLM = glm::determinant(glmTest);

			CHECK(detTest == Approx(detGLM));
			CHECK(testMat4::NearlyEqual(detTest, detGLM));

			test.Inverse();
			glmTest = glm::inverse(glmTest);

			detTest = test.Determinant();
			detGLM = glm::determinant(glmTest);

			CHECK(detTest == Approx(detGLM));
			CHECK(testMat4::NearlyEqual(detTest, detGLM));

			CHECK(test == glmTest);
		}

		SECTION("Matrix4 operator = ")
		{
			Matrix4 test2 = Matrix4::Identity();
			Matrix4 test = test2;

			REQUIRE(test[0][1] == 0);
			REQUIRE((test[0][0] == 1.f
				&& test[1][1] == 1.f
				&& test[2][2] == 1.f
				&& test[3][3] == 1.f));

			CHECK((test[0][0] == 1.f
				&& test[0][1] == 0.f
				&& test[0][2] == 0.f
				&& test[0][3] == 0.f
				&& test[1][0] == 0.f
				&& test[1][1] == 1.f
				&& test[1][2] == 0.f
				&& test[1][3] == 0.f
				&& test[2][0] == 0.f
				&& test[2][1] == 0.f
				&& test[2][2] == 1.f
				&& test[2][3] == 0.f
				&& test[3][0] == 0.f
				&& test[3][1] == 0.f
				&& test[3][2] == 0.f
				&& test[3][3] == 1.f
				));
		}

		SECTION("Matrix4 operator *")
		{
			Matrix4 test = Matrix4::Identity();
			glm::mat4 glmTest(1.f);
			test.Translate(1, 4, 9);
			glmTest = glm::translate(glmTest, { 1, 4, 9 });

			Vector4 vecTest(9, 10, 88, 1);
			glm::vec4 vecTest2(9, 10, 88, 1);

			Vector4 res1 = test * vecTest;
			glm::vec4 res2 = glmTest * vecTest2;

			CHECK(res1.x == res2.x);
			CHECK(res1.y == res2.y);
			CHECK(res1.z == res2.z);
			CHECK(res1.w == res2.w);
		}
		
		SECTION("Matrix4, Vector4 operator *")
		{
			Matrix4 test = Matrix4::Identity();
			glm::mat4 glmTest(1.f);
			test.Translate(1, 4, 9);
			glmTest = glm::translate(glmTest, { 1, 4, 9 });

			Vector4 vecTest(9, 10, 88, 1);
			glm::vec4 vecTest2(9, 10, 88, 1);

			Vector4 res1 = vecTest * test;
			glm::vec4 res2 = vecTest2 * glmTest;

			CHECK(res1.x == res2.x);
			CHECK(res1.y == res2.y);
			CHECK(res1.z == res2.z);
			CHECK(res1.w == res2.w);
		}
	}

	TEST_CASE("Matrix4 operation", "[Matrix4][Matrix44]")
	{
		Matrix4 test;
		test = Matrix4::Translation(2, 4, 9);
		Matrix4 reference = test;

		SECTION("Transpose")
		{
			test.Transpose();

			CHECK((test[0][0] == reference[0][0]
				&& test[0][1] == reference[1][0]
				&& test[0][2] == reference[2][0]
				&& test[0][3] == reference[3][0]
				&& test[1][0] == reference[0][1]
				&& test[1][1] == reference[1][1]
				&& test[1][2] == reference[2][1]
				&& test[1][3] == reference[3][1]
				&& test[2][0] == reference[0][2]
				&& test[2][1] == reference[1][2]
				&& test[2][2] == reference[2][2]
				&& test[2][3] == reference[3][2]
				&& test[3][0] == reference[0][3]
				&& test[3][1] == reference[1][3]
				&& test[3][2] == reference[2][3]
				&& test[3][3] == reference[3][3]
				));

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					std::stringstream str;
					str << "Transpose details : " << i << ", " << j;
					SECTION(str.str(), "[.][Details]")
					{
						CHECK(test[i][j] == reference[j][i]);
					}
				}
			}
		}
	}
}