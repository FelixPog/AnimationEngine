#include "Skeleton.h"

#include "AnimationClip.h"
#include "Engine.h"
#include "string"
#include "Data.h"

// BONE
Bone::Bone(unsigned pIndexParent, const char* pName, LibMath::Matrix4 pLocalTransform, LibMath::Matrix4 pGlobalTransform)
	: indexParent(pIndexParent), name(pName), localTransform(pLocalTransform), globalTransform(pGlobalTransform)
{
	inverseBindPose = globalTransform.GetInverse();
}

bool Bone::IsIK() const
{
	return name.find("ik_") == 0;
}

// SKELETON
void Skeleton::Init()
{
	m_bonesCount = GetSkeletonBoneCount();
	
	for (size_t boneIndex = 0; boneIndex < GetSkeletonBoneCount(); boneIndex++)
	{
		InitOneBone(boneIndex, GetSkeletonBoneParentIndex(boneIndex), GetSkeletonBoneName(boneIndex));
	}
}

const Bone* Skeleton::GetBoneByIndex(const unsigned index) const
{
	if (index < m_bones.size())
	{
		return &m_bones[index];
	}

	return nullptr;
}

void Skeleton::AddBone(const unsigned indexParent, const char* boneName, const LibMath::Matrix4& localTransform, const LibMath::Matrix4& globalTransform)
{
	if (boneName == nullptr)
	{
		return;
	}
	
	m_bones.emplace_back(indexParent, boneName, localTransform, globalTransform);
}

size_t Skeleton::GetBoneCount() const
{
	return m_bones.size();
}

void Skeleton::DrawBindPose() const
{
	for (size_t boneIndex = 1; boneIndex < GetBoneCount(); boneIndex++)
	{
		DrawOneBoneBindPose(boneIndex);
	}
}

void Skeleton::DrawOneBoneBindPose(const int boneIndex) const
{
	const Bone* bone = GetBoneByIndex(boneIndex);

	if (bone == nullptr || bone->IsIK())
	{
		return;
	}

	const LibMath::Vector4 start = bone->globalTransform.GetTranslation();
	const LibMath::Vector4 end = GetBoneByIndex(bone->indexParent)->globalTransform.GetTranslation();

	DrawLine(start.x, start.y + y_offset, start.z, end.x, end.y + y_offset, end.z, 0, 0, 0);
}

void Skeleton::InitOneBone(const int boneIndex, const int parentIndex, const char* name)
{
	Transform transform;
	GetSkeletonBoneLocalBindTransform(		static_cast<int>(boneIndex), transform.translation.x, transform.translation.y, transform.translation.z, 
											transform.rotation.W, transform.rotation.X, transform.rotation.Y, transform.rotation.Z);

	LibMath::Matrix4 localTransform(LibMath::Matrix4::Identity());
	localTransform.Rotate(transform.rotation);
	localTransform.Translate(transform.translation);

	LibMath::Matrix4 globalTransform(localTransform);
	if (boneIndex > 0)
	{
		globalTransform = GetBoneByIndex(parentIndex)->globalTransform * localTransform;
	}

	AddBone(parentIndex, name, localTransform, globalTransform);
}
