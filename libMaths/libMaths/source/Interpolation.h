#pragma once

namespace LibMath
{
	struct Quaternion;
	struct Vector3;

	namespace Interpolation
	{
		/**
		 * @brief All included ease functions shamelessly stolen from https://easings.net/
		 */
		enum class EaseFunctions
		{
			EASE_SINE,
			EASE_QUAD,
			EASE_CUBIC,
			EASE_QUART,
			EASE_QUINT,
			EASE_EXPO,
			EASE_CIRC,
			EASE_BACK,
			EASE_ELASTIC,
			EASE_BOUNCE,
		};

		/**
		 * @brief Will linearly interpolate a value between a start and end.
		 *
		 * @tparam T Requires [  T operator*(const float)  ] to be defined
		 * @param start The value that will be returned if delta is 0.f
		 * @param end The value that will be returned if delta is 1.f
		 * @param delta The percentage of interpolation between start and end
		 * @return T An interpolated value
		 */
		template <class T>
		T Lerp(const T& start, const T& end, const float delta)
		{
			return (start * (1.f - delta)) + (end * delta);
		}

		/**
		 * @brief Spherically interpolates two vectors (euler angles) between a start and end.
		 *
		 * @param start The value that will be returned if delta is 0.f
		 * @param end The value that will be returned if delta is 1.f
		 * @param delta The percentage of interpolation between start and end
		 * @return Vector3 The interpolated (angle) vector
		 */
		Vector3 Slerp(const Vector3& start, const Vector3& end, float delta);

		/**
		 * @brief Spherically interpolates two quaternions between a start and end.
		 * Implementation adapted from the Wikipedia article on Slerp
		 *
		 * @param start The value that will be returned if delta is 0.f
		 * @param end The value that will be returned if delta is 1.f
		 * @param delta The percentage of interpolation between start and end
		 * @return Quaternion The interpolated angle
		 */
		Quaternion Slerp(const Quaternion& start, const Quaternion& end, float delta);

		/**
		 * @brief Normalized lerp.
		 * Computationally less expensive than Slerp while yielding better results than a regular lerp.
		 *
		 * @param start The value that will be returned if delta is 0.f
		 * @param end The value that will be returned if delta is 1.f
		 * @param delta The percentage of interpolation between start and end
		 * @return Vector3 The interpolated (angle) vector
		 */
		Vector3 Nlerp(const Vector3& start, const Vector3& end, float delta);

		/**
		 * @brief Normalized lerp.
		 * Computationally less expensive than Slerp while yielding better results than a regular lerp.
		 *
		 * @param start The value that will be returned if delta is 0.f
		 * @param end The value that will be returned if delta is 1.f
		 * @param delta The percentage of interpolation between start and end
		 * @return Vector3 The interpolated quaternion
		 */
		Quaternion Nlerp(const Quaternion& start, const Quaternion& end, float delta);

		/**
		 * @brief A smoothing function that will return a value between start and end based on delta
		 *
		 * @param start The value that will be returned if delta is 0.f
		 * @param end The value that will be returned if delta is 1.f
		 * @param delta The percentage of interpolation between start and end
		 * @return float The smoothed interpolated value
		 */
		float SmoothStep(float start, float end, float delta);

		/**
		 * @brief A smoother smoothing function that will return a value between start and end based on delta
		 *
		 * @param start The value that will be returned if delta is 0.f
		 * @param end The value that will be returned if delta is 1.f
		 * @param delta The percentage of interpolation between start and end
		 * @return float The smoothed interpolated value
		 */
		float SmootherStep(float start, float end, float delta);

		/**
		 * @brief Takes a value between inMin and inMax and returns its value relative to outMin and outMax
		 *
		 * @param value The value to be mapped
		 * @param inMin The lower bounds of the input range
		 * @param inMax The upper bounds of the input range
		 * @param outMin The lower bounds of the output range
		 * @param outMax The upper bounds of the output range
		 * @return float The mapped value
		 */
		float MapInRange(float value, float inMin, float inMax, float outMin, float outMax);

		/**
		 * @brief A collection of ease in functions.
		 * See definition of the enum EaseFunctions to see what they look like. 
		 *
		 * @param delta Value between 0 and 1 that decides how far through the curve to return
		 * @param easeFunction The ease funtion to perform
		 * @return float The returned relative value
		 */
		float EaseIn(float delta, EaseFunctions easeFunction);

		/**
		 * @brief A collection of ease out functions.
		 * See definition of the enum EaseFunctions to see what they look like. 
		 *
		 * @param delta Value between 0 and 1 that decides how far through the curve to return
		 * @param easeFunction The ease funtion to perform
		 * @return float The returned relative value
		 */
		float EaseOut(float delta, EaseFunctions easeFunction);

		/**
		 * @brief A collection of ease in/out functions.
		 * See definition of the enum EaseFunctions to see what they look like. 
		 *
		 * @param delta Value between 0 and 1 that decides how far through the curve to return
		 * @param easeFunction The ease funtion to perform
		 * @return float The returned relative value
		 */
		float EaseInOut(float delta, EaseFunctions easeFunction);
	}
}
