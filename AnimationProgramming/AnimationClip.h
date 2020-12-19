#pragma once

#include <string>
#include <vector>

#include "Matrix/Matrix4.h"

class Skeleton;

struct Transform
{
	Transform() = default;
	Transform(const LibMath::Vector3& pTranslation, const LibMath::Quaternion& pRotation);
	Transform(const Transform& other) = default;

	Transform operator*(const Transform& other) const;
	LibMath::Vector3 translation;
	LibMath::Quaternion rotation;
};

class KeyFrame
{
public:
	KeyFrame(const int keyIndex);

	void InitTransform(const Skeleton* skeleton, KeyFrame* animationPose, const int boneIndex, const char* animName);
	
	void AddTransform(const Transform& transform);

	[[nodiscard]] int GetIndex() const;
	[[nodiscard]] const Transform& GetTransform(const int boneIndex) const;
	
private:
	int m_index;
	std::vector<Transform> m_transforms;
};

class AnimationClip
{
public:
	void Init(const Skeleton* skeleton, const char* name, const int duration);
	void InitKeyFrame(const Skeleton* skeleton, KeyFrame* animationPose, const char* animName);
	
	[[nodiscard]] KeyFrame* AddKeyFrame(const int keyIndex);

	[[nodiscard]] const Transform& GetBoneTransform(const int keyIndex, const int boneIndex) const;
	[[nodiscard]] const std::string& GetName() const;
	[[nodiscard]] int GetKeyCount() const;

	[[nodiscard]] int GetKeyToDraw() const;
	[[nodiscard]] float GetInterpolateValue() const;

	void UpdateKeyToDraw(const float deltaTime);

	void DrawAnimSkeleton(const int keyToDraw);	
	void GoToNextKey();

	void UpdateAnimMatrices(const float deltaTime);
	void SendAnimMatricesToShader();

	[[nodiscard]] const LibMath::Matrix4& GetAnimMatrixByIndex(const int boneIndex) const;

	[[nodiscard]] bool HaveSameSkeleton(const AnimationClip& other) const;

	[[nodiscard]] LibMath::Quaternion InterpolateRotation(const int keyIndex, const int boneIndex, const float interpolateValue) const;
	[[nodiscard]] LibMath::Vector3 InterpolateTranslation(const int keyIndex, const int boneIndex, const float interpolateValue) const;
	
private:
	void DrawAnimOneBoneSkeleton(const int indexKey, const int boneIndex);
	
	std::string m_name = "No Name";
	size_t m_keyCount = 0;
	float m_timeBetweenKey = 0.0f;
	float m_timeBeforeNextKey = 0.0f;

	int m_currentKeyToDraw = 0;
	float m_interpolateValue = 0.0f;

	std::vector<KeyFrame> m_keyFrames;

	const Skeleton* m_skeleton = nullptr;
	
	std::vector<LibMath::Matrix4>  m_animMatrices;
};

