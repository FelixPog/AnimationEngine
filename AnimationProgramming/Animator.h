#pragma once

#include <vector>
#include "AnimationClip.h"

class Animator
{
public:
	const AnimationClip* AddAnimationClip(const Skeleton* skeleton, const char* name, const float duration);

	[[nodiscard]] AnimationClip& MutateAnimationClipByIndex(const int index);

	void BlendAnimation(const float blendingRatio, const Skeleton& skeleton, const AnimationClip& sourceAnim, const AnimationClip& destinationAnim);
	[[nodiscard]] LibMath::Matrix4 CreateBlendMatrix(const float blendingRatio, const Transform& firstAnimTransform, const Transform& secondAnimTransform, const LibMath::Matrix4& inverseBindPose) const;
	
private:
	inline void ResetBlendMatricesVector(const size_t vectorSize);
	
	std::vector<AnimationClip> m_animationClips;
	std::vector<LibMath::Matrix4> m_blendMatrices;
};