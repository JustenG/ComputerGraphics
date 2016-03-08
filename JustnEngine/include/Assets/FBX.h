#pragma once
#include "gl_core_4_4.h"
#include "Assets\Mesh.h"

class FBXFile;
class FBXSkeleton;
class FBXAnimation;
class VertexArrayObject;
class Shader;

class FBX : public Mesh
{
public:
	FBX();
	~FBX();

	//bool LoadFBX(const char* filename);

	void Update(float deltaTime);

	//FBXFile* GetFBX();
	FBXSkeleton* GetSkeleton();

	//const char** GetTexturePath();

private:

	FBXSkeleton* m_skeleton;
	FBXAnimation* m_animation;

	bool hasLoaded;
	int textureCount;

	float m_time;

};

