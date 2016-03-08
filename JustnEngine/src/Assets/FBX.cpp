#include "Assets/FBX.h"

#include "gl_core_4_4.h"
#include "FBXFile.h"

FBX::FBX()
{
	hasLoaded = false;

	m_skeleton = new FBXSkeleton();
	m_animation = new FBXAnimation();
	m_time = 0;

}

FBX::~FBX()
{

}

//const char** FBX::GetTexturePath()
//{
//	//const char** pathArray = new const char*[textureCount];
//	//for (int i = 0; i < textureCount; ++i)
//	//{
//	//	pathArray[i] = texture->path.c_str();
//	//}
//	//return pathArray;
//}

void FBX::Update(float deltaTime)
{
	//m_time += deltaTime;
	//// evaluate the animation to update bones
	//m_skeleton->evaluate(m_animation, m_time);
	//for (GLuint i = 0; i < m_skeleton->m_boneCount; ++i)
	//{
	//	m_skeleton->m_nodes[i]->updateGlobalTransform();
	//}

	//// grab the skeleton and animation we want to use
	//m_skeleton->updateBones();
}

FBXSkeleton* FBX::GetSkeleton()
{
	return m_skeleton;
}
