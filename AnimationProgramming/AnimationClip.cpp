#include "AnimationClip.h"
#include "Quaternion/Quaternion.h"
#include "Skeleton.h"
#include "Data.h"
#include "Interpolation.h"
#include "Engine.h"

// TRANSFORM
Transform::Transform(const LibMath::Vector3& pTranslation, const LibMath::Quaternion& pRotation)
{
	translation = pTranslation;
	rotation = pRotation;
}

Transform Transform::operator*(const Transform& other) const
{
	Transform transform;
	transform.translation = (other.rotation * this->translation) + other.translation;
	transform.rotation = other.rotation * this->rotation;
	
	return transform;
}

// KEY FRAME
KeyFrame::KeyFrame(const int keyIndex)
	: m_index(keyIndex)
{}

void KeyFrame::InitTransform(const Skeleton* skeleton, KeyFrame* animationPose, const int boneIndex, const char* animName)
{
	if (skeleton == nullptr || animationPose == nullptr)
	{
		return;
	}
	const Bone* bone = skeleton->GetBoneByIndex(boneIndex);

	if (bone == nullptr || bone->IsIK())
	{
		return;
	}

	// TODO Replace by getting saved local transform
	Transform bindPoseTransform;
	GetSkeletonBoneLocalBindTransform(boneIndex, bindPoseTransform.translation.x, bindPoseTransform.translation.y, bindPoseTransform.translation.z, bindPoseTransform.rotation.W, bindPoseTransform.rotation.X, bindPoseTransform.rotation.Y, bindPoseTransform.rotation.Z);

	Transform animTransform;
	GetAnimLocalBoneTransform(animName, boneIndex, animationPose->GetIndex(), animTransform.translation.x, animTransform.translation.y, animTransform.translation.z, animTransform.rotation.W, animTransform.rotation.X, animTransform.rotation.Y, animTransform.rotation.Z);

	animTransform = animTransform * bindPoseTransform;

	if (boneIndex > 0)
	{
		const Transform& parentTransform = animationPose->GetTransform(bone->indexParent);
		animTransform = animTransform * parentTransform;
	}

	animationPose->AddTransform(animTransform);
}

void KeyFrame::AddTransform(const Transform& transform)
{
	m_transforms.emplace_back(transform);
}

int KeyFrame::GetIndex() const
{
	return m_index;
}

const Transform& KeyFrame::GetTransform(const int boneIndex) const
{
	return m_transforms[boneIndex];
}

// ANIMATION CLIP

void AnimationClip::Init(const Skeleton* skeleton, const char* name, const int duration)
{
	if (skeleton == nullptr || name == nullptr)
	{
		return;
	}
	
	m_name = name;
	m_keyCount = GetAnimKeyCount(name);
	m_timeBetweenKey = static_cast<float>(duration) / static_cast<float>(m_keyCount);
	m_timeBeforeNextKey = m_timeBetweenKey;
	m_skeleton = skeleton;

	for (size_t keyFrame = 0; keyFrame < m_keyCount; keyFrame++)
	{
		InitKeyFrame(m_skeleton, AddKeyFrame(keyFrame), name);
	}
}

void AnimationClip::InitKeyFrame(const Skeleton* skeleton, KeyFrame* animationPose, const char* animName)
{
	if (skeleton == nullptr || animationPose == nullptr || animName == nullptr)
	{
		return;
	}

	for (size_t boneIndex = 0; boneIndex < m_skeleton->GetBoneCount(); boneIndex++)
	{
		animationPose->InitTransform(skeleton, animationPose, boneIndex, animName);
	}
}

KeyFrame* AnimationClip::AddKeyFrame(const int keyIndex)
{
	m_keyFrames.emplace_back(keyIndex);
	return &m_keyFrames[m_keyFrames.size() - 1];
}

const Transform& AnimationClip::GetBoneTransform(const int keyIndex, const int boneIndex) const
{
	return m_keyFrames[keyIndex].GetTransform(boneIndex);
}

const std::string& AnimationClip::GetName() const
{
	return m_name;
}

int AnimationClip::GetKeyCount() const
{
	return m_keyCount;
}

int AnimationClip::GetKeyToDraw() const
{
	return m_currentKeyToDraw;
}

float AnimationClip::GetInterpolateValue() const
{
	return m_interpolateValue;
}

void AnimationClip::UpdateKeyToDraw(const float deltaTime)
{
	m_timeBeforeNextKey -= deltaTime;
	m_interpolateValue += deltaTime / m_timeBetweenKey;
	
	while (m_timeBeforeNextKey <= 0.0f)
	{
		GoToNextKey();
		m_interpolateValue -= 1.0f;
	}
}


void AnimationClip::GoToNextKey()
{
	m_currentKeyToDraw++;
	
	if (m_currentKeyToDraw > static_cast<int>(m_keyCount) - 1)
	{
		m_currentKeyToDraw = 0;
	}
	
	m_timeBeforeNextKey += m_timeBetweenKey ;
}

void AnimationClip::DrawAnimSkeleton(const int keyToDraw)
{
	if (m_skeleton == nullptr)
	{
		return;
	}
	
	for (size_t nbBone = 1; nbBone < m_skeleton->GetBoneCount(); nbBone++)
	{
		DrawAnimOneBoneSkeleton(keyToDraw, nbBone);
	}
}


void AnimationClip::UpdateAnimMatrices(const float deltaTime)
{			
	if (m_skeleton == nullptr)
	{
		return;
	}
	m_animMatrices.clear();
	
	m_animMatrices.reserve(61);

	for (size_t nbBone = 0; nbBone < m_skeleton->GetBoneCount() - nb_of_ik_bone; nbBone++)
	{				
		LibMath::Matrix4 matAnim = LibMath::Matrix4::Identity();
		matAnim.Rotate(InterpolateRotation(m_currentKeyToDraw, nbBone, m_interpolateValue));
		matAnim.Translate(InterpolateTranslation(m_currentKeyToDraw, nbBone, m_interpolateValue));

		matAnim *= m_skeleton->GetBoneByIndex(nbBone)->inverseBindPose;

		m_animMatrices.push_back(matAnim);
	}	
}

void AnimationClip::SendAnimMatricesToShader()
{
	if (m_skeleton == nullptr)
	{
		return;
	}
	
	SetSkinningPose(reinterpret_cast<float*>(m_animMatrices.data()), m_skeleton->GetBoneCount() - nb_of_ik_bone);
}

const LibMath::Matrix4& AnimationClip::GetAnimMatrixByIndex(const int boneIndex) const
{
	return m_animMatrices[boneIndex];
}

bool AnimationClip::HaveSameSkeleton(const AnimationClip& other) const
{
	return m_skeleton == other.m_skeleton;
}

LibMath::Quaternion AnimationClip::InterpolateRotation(const int keyIndex, const int boneIndex, const float interpolateValue) const
{
	LibMath::Quaternion firstKeyRotation = GetBoneTransform(keyIndex, boneIndex).rotation;
	LibMath::Quaternion secondKeyRotation;

	if (keyIndex == m_keyCount - 1)
	{
		secondKeyRotation = GetBoneTransform(0, boneIndex).rotation;
	}
	else
	{
		secondKeyRotation = GetBoneTransform(keyIndex + 1, boneIndex).rotation;
	}

	return LibMath::Interpolation::Slerp(firstKeyRotation, secondKeyRotation, m_interpolateValue);
}

LibMath::Vector3 AnimationClip::InterpolateTranslation(const int keyIndex, const int boneIndex, const float interpolateValue) const
{
	LibMath::Vector3 firstKeyTranslation = GetBoneTransform(keyIndex, boneIndex).translation;
	LibMath::Vector3 secondKeyTranslation;

	if (keyIndex == m_keyCount - 1)
	{
		secondKeyTranslation = GetBoneTransform(0, boneIndex).translation;
	}
	else
	{
		secondKeyTranslation = GetBoneTransform(keyIndex + 1, boneIndex).translation;
	}

	return LibMath::Interpolation::Lerp(firstKeyTranslation, secondKeyTranslation, m_interpolateValue);
}

void AnimationClip::DrawAnimOneBoneSkeleton(const int indexKey, const int boneIndex)
{
	if (m_skeleton == nullptr)
	{
		return;
	}
	
	const Bone* bone = m_skeleton->GetBoneByIndex(boneIndex);

	if (bone == nullptr || bone->IsIK())
	{
		return;
	}
	const Transform& sqt = GetBoneTransform(indexKey, boneIndex);
	const Transform& sqtParent = GetBoneTransform(indexKey, bone->indexParent);

	DrawLine(sqt.translation.x, sqt.translation.y + y_offset, sqt.translation.z, sqtParent.translation.x, sqtParent.translation.y + y_offset, sqtParent.translation.z, 1, 0, 1);
}
