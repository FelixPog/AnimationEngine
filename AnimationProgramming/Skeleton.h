#pragma once

#include <string>
#include <vector>
#include <Matrix/Matrix4.h>


struct Bone
{
	
	Bone(unsigned int pIndexParent, const char* pName, LibMath::Matrix4 pLocalTransform, LibMath::Matrix4 pGlobalTransform);
	[[nodiscard]] bool IsIK() const;

	unsigned int indexParent = 0;
	std::string name = "No_Name";
	LibMath::Matrix4 localTransform;
	LibMath::Matrix4 globalTransform;
	LibMath::Matrix4 inverseBindPose;
};

class Skeleton
{
public:	
	void Init();
	
	[[nodiscard]] const Bone* GetBoneByIndex(const unsigned int index) const;
	[[nodiscard]] size_t GetBoneCount() const;

	void DrawBindPose() const;
private:
	void InitOneBone(const int boneIndex, const int parentIndex, const char* name);

	void AddBone(const unsigned indexParent, const char* boneName, const LibMath::Matrix4& localTransform, const LibMath::Matrix4& globalTransform);
	
	void DrawOneBoneBindPose(const int boneIndex) const;

	int m_bonesCount = 0;
	std::vector<Bone> m_bones;
};