#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "gl_core_4_4.h"
#include "Assets\Material.h"


class VertexArrayObject;
class Shader;
class Material;
class FBXMeshNode;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void LoadFile(std::string fileName);
	void LoadFBX(std::string fileName);
	void LoadShader(const GLchar* vertexPath, const GLchar* fragmentPath);

private:

	void SetShader(Shader* shader);

	void BuildRenderDataFromLoaderNode(VertexArrayObject** pRenderData, FBXMeshNode* pMesh);

	template<typename T>
	void BuildMaterialFromLoaderNode(Material** pMaterial, T* pLoaderMaterial)
	{
		*pMaterial = new Material();
		(*pMaterial)->InitializeFromLoaderMaterial(pLoaderMaterial);

	}

	VertexArrayObject* m_pRenderObject;
	Shader* m_pShader;
	Material* m_pMaterial;

	GLuint* m_pData;
	std::vector<Mesh*> m_internalMeshes;

};

