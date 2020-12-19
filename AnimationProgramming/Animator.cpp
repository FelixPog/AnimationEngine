#include "Animator.h"

#include <Interpolation.h>

#include "Data.h"
#include "Engine.h"
#include "Skeleton.h"

const AnimationClip* Animator::AddAnimationClip(const Skeleton* skeleton, const char* name, const float duration)
{
	if (skeleton == nullptr || name == nullptr)
	{
		return nullptr;
	}

	m_animationClips.emplace_back(AnimationClip());
	m_animationClips[m_animationClips.size() - 1].Init(skeleton, name, duration);

	return &m_animationClips[m_animationClips.size() - 1];
}

AnimationClip& Animator::MutateAnimationClipByIndex(const int index)
{
	return m_animationClips[index];
}

void Animator::BlendAnimation(const float blendingRatio, const Skeleton& skeleton, const AnimationClip& sourceAnim, const AnimationClip& destinationAnim)
{
	if (!sourceAnim.HaveSameSkeleton(destinationAnim))
	{
		return;
	}

	if (blendingRatio < 0.0f && blendingRatio > 1.0f)
	{
		printf("Blending ratio should be between 0 and 1, here it is : %f", blendingRatio);
	}

	// Init value used for Interpolation
	const float timeScale = static_cast<float>(destinationAnim.GetKeyCount()) / static_cast<float>(sourceAnim.GetKeyCount());
	
	const int keyPlayedSourceAnim = sourceAnim.GetKeyToDraw();
	const float interpolateValueSourceAnim = sourceAnim.GetInterpolateValue();
	const float preciseKeyPlayedSourceAnim = (static_cast<float>(keyPlayedSourceAnim) + interpolateValueSourceAnim) * timeScale;
	
	const int keyPlayedDestinationAnim = static_cast<int>(preciseKeyPlayedSourceAnim);
	const float interpolateValueDestinationAnim = preciseKeyPlayedSourceAnim - static_cast<float>(keyPlayedDestinationAnim);
		
	ResetBlendMatricesVector(skeleton.GetBoneCount() - nb_of_ik_bone);

	for (size_t nbBone = 0; nbBone < skeleton.GetBoneCount() - nb_of_ik_bone; nbBone++)
	{
		Transform firstAnimTransform(	sourceAnim.InterpolateTranslation(keyPlayedSourceAnim, nbBone, interpolateValueSourceAnim),
										sourceAnim.InterpolateRotation(keyPlayedSourceAnim, nbBone, interpolateValueSourceAnim));

		Transform secondAnimTransform(	destinationAnim.InterpolateTranslation(keyPlayedDestinationAnim, nbBone, interpolateValueDestinationAnim),
										destinationAnim.InterpolateRotation(keyPlayedDestinationAnim, nbBone, interpolateValueDestinationAnim));

		m_blendMatrices.push_back(CreateBlendMatrix(blendingRatio, firstAnimTransform, secondAnimTransform, skeleton.GetBoneByIndex(nbBone)->inverseBindPose));
	}

	// Send matrices vector to vertex shader "skinning.vs"
	SetSkinningPose(reinterpret_cast<float*>(m_blendMatrices.data()),  skeleton.GetBoneCount() - nb_of_ik_bone);
}

LibMath::Matrix4 Animator::CreateBlendMatrix(const float blendingRatio, const Transform& firstAnimTransform, const Transform& secondAnimTransform, const LibMath::Matrix4& inverseBindPose) const
{
	LibMath::Matrix4 blendMatrix(LibMath::Matrix4::Identity());
	blendMatrix.Rotate(LibMath::Interpolation::Slerp(firstAnimTransform.rotation, secondAnimTransform.rotation, blendingRatio));
	blendMatrix.Translate(LibMath::Interpolation::Lerp(firstAnimTransform.translation, secondAnimTransform.translation, blendingRatio));

	return blendMatrix *= inverseBindPose;
}

void Animator::ResetBlendMatricesVector(const size_t vectorSize)
{
	m_blendMatrices.clear();
	
	if (vectorSize > 64)
	{
		printf("WARNING : WhiteBox library can only take 64 bones, the skeleton loaded have : %d bones\n", vectorSize);
		m_blendMatrices.reserve(64);
		return;
	}
	
	m_blendMatrices.reserve(vectorSize);
}
