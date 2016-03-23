#pragma once
#include "Assets\Asset.h"

#include <vector>
#include <iostream>
#include <string>
#include "gl_core_4_4.h"

class Mesh;
class Shader;
class FBXFile;

class MeshFile : public Asset
{
public:
	MeshFile();
	~MeshFile();

	void LoadFile(std::string fileName);
	void LoadFBX(std::string fileName);

	void Update();

	void CreateEntitys();

private:

	void onBind() override;
	void onUnbind() override;

	FBXFile* m_fbxFile;
	std::vector<Mesh*> m_internalMeshes;

	Shader* m_pShader;
};

