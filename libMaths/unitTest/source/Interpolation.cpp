#include "Interpolation.h"

#include <catch2/catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Quaternion/Quaternion.h"
#include "Vector/Vector3.h"

using namespace LibMath;

namespace LibMath::Interpolation
{
	TEST_CASE("Test Interpolation", "[LibMaths]")
	{
		SECTION("Lerp")
		{
			/*
			 * Floats
			 */
			{
				// Check Zero
				float start = 0.f;
				float end = 1.f;
				float delta = 0.0f;
				float result = Lerp(start, end, delta);
				float expected = glm::mix(start, end, delta);
				CHECK(result == Approx(expected).epsilon(0.0005f));

				// Check Halfway
				start = 0.f;
				end = 1.f;
				delta = 0.5f;
				result = Lerp(start, end, delta);
				expected = glm::mix(start, end, delta);
				CHECK(result == Approx(expected).epsilon(0.0005f));

				// Check One
				start = 0.f;
				end = 1.f;
				delta = 1.f;
				result = Lerp(start, end, delta);
				expected = glm::mix(start, end, delta);
				CHECK(result == Approx(expected).epsilon(0.0005f));

				// Check Negative
				start = 0.f;
				end = 1.f;
				delta = -0.5f;
				result = Lerp(start, end, delta);
				expected = glm::mix(start, end, delta);
				CHECK(result == Approx(expected).epsilon(0.0005f));

				// Check Random
				start = 2.f;
				end = 27.f;
				delta = 0.7f;
				result = Lerp(start, end, delta);
				expected = glm::mix(start, end, delta);
				CHECK(result == Approx(expected).epsilon(0.0005f));
			}

			/*
			 * Vector3
			 */
			{
				// Check zero
				Vector3 start = Vector3(0.f);
				Vector3 end = Vector3(1.f);
				float delta = 0.f;
				Vector3 result = Lerp(start, end, delta);

				glm::vec3 glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				Vector3 expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));

				// Check Halfway
				start = Vector3(0.f);
				end = Vector3(1.f);
				delta = 0.5f;
				result = Lerp(start, end, delta);
				glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));

				// Check One
				start = Vector3(0.f);
				end = Vector3(1.f);
				delta = 1.f;
				result = Lerp(start, end, delta);
				glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));

				// Check Negative
				start = Vector3(0.f);
				end = Vector3(1.f);
				delta = -0.5f;
				result = Lerp(start, end, delta);
				glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));

				// Check Random
				start = Vector3(2.f, 1.f, 3.f);
				end = Vector3(27.f, 120.f, 14.f);
				delta = 0.7f;
				result = Lerp(start, end, delta);
				glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));
			}

			/*
			 * Quaternion
			 */
			{
				// Check zero
				Quaternion start = Quaternion(0.f, 0.f, 0.f, 0.f);
				Quaternion end = Quaternion(1.f, 1.f, 1.f, 1.f);
				float delta = 0.f;
				Quaternion result = Lerp(start, end, delta);

				glm::quat glmExpected = glm::lerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, delta);
				Quaternion expected = Quaternion(glmExpected.x, glmExpected.y, glmExpected.z, glmExpected.w);
				CHECK(result.X == Approx(expected.X).epsilon(0.0005f));
				CHECK(result.Y == Approx(expected.Y).epsilon(0.0005f));
				CHECK(result.Z == Approx(expected.Z).epsilon(0.0005f));
				CHECK(result.W == Approx(expected.W).epsilon(0.0005f));

				// Check Halfway
				start = Quaternion(0.f, 0.f, 0.f, 0.f);
				end = Quaternion(1.f, 1.f, 1.f, 1.f);
				delta = 0.5f;
				result = Lerp(start, end, delta);

				glmExpected = glm::lerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, delta);
				expected = Quaternion(glmExpected.x, glmExpected.y, glmExpected.z, glmExpected.w);
				CHECK(result.X == Approx(expected.X).epsilon(0.0005f));
				CHECK(result.Y == Approx(expected.Y).epsilon(0.0005f));
				CHECK(result.Z == Approx(expected.Z).epsilon(0.0005f));
				CHECK(result.W == Approx(expected.W).epsilon(0.0005f));

				// Check One
				start = Quaternion(0.f, 0.f, 0.f, 0.f);
				end = Quaternion(1.f, 1.f, 1.f, 1.f);
				delta = 1.f;
				result = Lerp(start, end, delta);
				glmExpected = glm::lerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, delta);
				expected = Quaternion(glmExpected.x, glmExpected.y, glmExpected.z, glmExpected.w);
				CHECK(result.X == Approx(expected.X).epsilon(0.0005f));
				CHECK(result.Y == Approx(expected.Y).epsilon(0.0005f));
				CHECK(result.Z == Approx(expected.Z).epsilon(0.0005f));
				CHECK(result.W == Approx(expected.W).epsilon(0.0005f));

				// Check Random
				start = Quaternion(4.f, 26.f, 17.f, 3.f);
				end = Quaternion(111.f, 14.f, 1.f, 6.f);
				delta = 0.7f;
				result = Lerp(start, end, delta);
				glmExpected = glm::lerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, delta);
				expected = Quaternion(glmExpected.x, glmExpected.y, glmExpected.z, glmExpected.w);
				CHECK(result.X == Approx(expected.X).epsilon(0.0005f));
				CHECK(result.Y == Approx(expected.Y).epsilon(0.0005f));
				CHECK(result.Z == Approx(expected.Z).epsilon(0.0005f));
				CHECK(result.W == Approx(expected.W).epsilon(0.0005f));
			}
		}

		SECTION("Slerp")
		{
			// Check zero
			Quaternion start = Quaternion(5.f, -3.f, 7.f, 0.f);
			Quaternion end = Quaternion(2.f, 1.f, 4.5f, 1.f);

			for (float alpha = -1.1f; alpha <= 1.1f; alpha = alpha + 0.001f)
			{
				Quaternion result = Slerp(start, end, alpha);
				glm::quat glmExpected = glm::slerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, alpha);

				CHECK(result.X == Approx(glmExpected.x).epsilon(0.0005f));
				CHECK(result.Y == Approx(glmExpected.y).epsilon(0.0005f));
				CHECK(result.Z == Approx(glmExpected.z).epsilon(0.0005f));
				CHECK(result.W == Approx(glmExpected.w).epsilon(0.0005f));
			}

			start = Quaternion(Degree(110), Degree(-50), Degree(30));
			end = Quaternion(Degree(60), Degree(10), Degree(100));
			for (float alpha = -1.1f; alpha <= 1.1f; alpha = alpha + 0.001f)
			{
				Quaternion result = Slerp(start, end, alpha);
				glm::quat glmExpected = glm::slerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, alpha);

				CHECK(result.X == Approx(glmExpected.x).epsilon(0.0005f));
				CHECK(result.Y == Approx(glmExpected.y).epsilon(0.0005f));
				CHECK(result.Z == Approx(glmExpected.z).epsilon(0.0005f));
				CHECK(result.W == Approx(glmExpected.w).epsilon(0.0005f));
			}
		}

		SECTION("Nlerp")
		{
			/*
			 * Vector3
			 */
			{
				// Check zero
				Vector3 start = Vector3(0.1f);
				Vector3 end = Vector3(1.f);
				float delta = 0.f;
				Vector3 result = Nlerp(start, end, delta);

				glm::vec3 glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				glmExpected = glm::normalize(glmExpected);
				Vector3 expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));

				// Check Halfway
				start = Vector3(0.1f);
				end = Vector3(1.f);
				delta = 0.5f;
				result = Nlerp(start, end, delta);

				glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				glmExpected = glm::normalize(glmExpected);
				expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));

				// Check One
				start = Vector3(0.1f);
				end = Vector3(1.f);
				delta = 1.f;
				result = Nlerp(start, end, delta);

				glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				glmExpected = glm::normalize(glmExpected);
				expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));

				// Check Negative
				start = Vector3(0.1f);
				end = Vector3(1.f);
				delta = -0.5f;
				result = Nlerp(start, end, delta);

				glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				glmExpected = glm::normalize(glmExpected);
				expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));

				// Check Random
				start = Vector3(2.f, 1.f, 3.f);
				end = Vector3(27.f, 120.f, 14.f);
				delta = 0.7f;
				result = Nlerp(start, end, delta);

				glmExpected = glm::mix(glm::vec3{ start.x, start.y, start.z }, glm::vec3{ end.x, end.y, end.z }, delta);
				glmExpected = glm::normalize(glmExpected);
				expected = Vector3(glmExpected.x, glmExpected.y, glmExpected.z);
				CHECK(result.x == Approx(expected.x).epsilon(0.0005f));
				CHECK(result.y == Approx(expected.y).epsilon(0.0005f));
				CHECK(result.z == Approx(expected.z).epsilon(0.0005f));
			}

			/*
			 * Quaternion
			 */
			{
				// Check zero
				Quaternion start = Quaternion(0.f, 0.f, 0.f, 0.f);
				Quaternion end = Quaternion(1.f, 1.f, 1.f, 1.f);
				float delta = 0.f;
				Quaternion result = Nlerp(start, end, delta);

				glm::quat glmExpected = glm::lerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, delta);
				glmExpected = glm::normalize(glmExpected);
				Quaternion expected = Quaternion(glmExpected.x, glmExpected.y, glmExpected.z, glmExpected.w);
				CHECK(result.X == Approx(expected.X).epsilon(0.0005f));
				CHECK(result.Y == Approx(expected.Y).epsilon(0.0005f));
				CHECK(result.Z == Approx(expected.Z).epsilon(0.0005f));
				CHECK(result.W == Approx(expected.W).epsilon(0.0005f));

				// Check Halfway
				start = Quaternion(0.f, 0.f, 0.f, 0.f);
				end = Quaternion(1.f, 1.f, 1.f, 1.f);
				delta = 0.5f;
				result = Nlerp(start, end, delta);

				glmExpected = glm::lerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, delta);
				glmExpected = glm::normalize(glmExpected);
				expected = Quaternion(glmExpected.x, glmExpected.y, glmExpected.z, glmExpected.w);
				CHECK(result.X == Approx(expected.X).epsilon(0.0005f));
				CHECK(result.Y == Approx(expected.Y).epsilon(0.0005f));
				CHECK(result.Z == Approx(expected.Z).epsilon(0.0005f));
				CHECK(result.W == Approx(expected.W).epsilon(0.0005f));

				// Check One
				start = Quaternion(0.f, 0.f, 0.f, 0.f);
				end = Quaternion(1.f, 1.f, 1.f, 1.f);
				delta = 1.f;
				result = Nlerp(start, end, delta);
				glmExpected = glm::lerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, delta);
				glmExpected = glm::normalize(glmExpected);
				expected = Quaternion(glmExpected.x, glmExpected.y, glmExpected.z, glmExpected.w);
				CHECK(result.X == Approx(expected.X).epsilon(0.0005f));
				CHECK(result.Y == Approx(expected.Y).epsilon(0.0005f));
				CHECK(result.Z == Approx(expected.Z).epsilon(0.0005f));
				CHECK(result.W == Approx(expected.W).epsilon(0.0005f));

				// Check Random
				start = Quaternion(4.f, 26.f, 17.f, 3.f);
				end = Quaternion(111.f, 14.f, 1.f, 6.f);
				delta = 0.7f;
				result = Nlerp(start, end, delta);
				glmExpected = glm::lerp(glm::quat{ start.W, start.X, start.Y , start.Z }, glm::quat{ end.W, end.X, end.Y, end.Z }, delta);
				glmExpected = glm::normalize(glmExpected);
				expected = Quaternion(glmExpected.x, glmExpected.y, glmExpected.z, glmExpected.w);
				CHECK(result.X == Approx(expected.X).epsilon(0.0005f));
				CHECK(result.Y == Approx(expected.Y).epsilon(0.0005f));
				CHECK(result.Z == Approx(expected.Z).epsilon(0.0005f));
				CHECK(result.W == Approx(expected.W).epsilon(0.0005f));
			}
		}

		SECTION("SmoothStep")
		{
		}

		SECTION("SmootherStep")
		{
		}

		SECTION("MapInRange")
		{
		}
	}
}