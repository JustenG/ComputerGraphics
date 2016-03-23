#pragma once
#include "Assets\Asset.h"

#include <vector>
#include <iostream>
#include <string>
#include "gl_core_4_4.h"


class VertexArrayObject;
class Shader;
class Material;
class FBXMeshNode;
class Transform;
class Camera;
class Component;
class Light;

class Mesh : public Asset
{
public:
	Mesh();
	~Mesh();

	void Update();
	void Render();

	void BuildRenderDataFromLoaderNode(FBXMeshNode* pMesh);
	template<typename T>
	void BuildMaterialFromLoaderNode(T* pLoaderMaterial)
	{
		m_pAssetManager->CreateMaterial(GetFileName());
		m_pMaterial = m_pAssetManager->GetAsset<Material>(GetFileName());

		m_pMaterial->InitializeFromLoaderMaterial(pLoaderMaterial);

	}

private:

	void onBind() override;
	void onUnbind() override;

	VertexArrayObject* m_pRenderObject;
	Material* m_pMaterial;

};

