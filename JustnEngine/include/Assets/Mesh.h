#pragma once
#include "Assets\Asset.h"

#include <vector>
#include <iostream>
#include <string>
#include "gl_core_4_4.h"

#include "Assets\Material.h"

class VertexArrayObject;
class Material;
class FBXMeshNode;
class Vertex;

class Mesh : public Asset
{
public:
	Mesh();
	~Mesh();

	void Update();
	void Render();

	Material* GetMaterial() { return m_pMaterial; };

	void BuildRenderDataFromLoaderNode(FBXMeshNode* pMesh);
	void BuildRenderDataFromLoaderNode(GLuint vertexCount, GLuint indicesCount, Vertex* vertexData, GLuint* indicesData);

	template<typename T>
	void BuildMaterialFromLoaderNode(T* pLoaderMaterial, std::string name)
	{
		m_pAssetManager->CreateMaterial(name);
		m_pMaterial = m_pAssetManager->GetAsset<Material>(name);

		m_pMaterial->InitializeFromLoaderMaterial(pLoaderMaterial);
	}

private:

	void onBind() override;
	void onUnbind() override;

	VertexArrayObject* m_pRenderObject;
	Material* m_pMaterial;

};

