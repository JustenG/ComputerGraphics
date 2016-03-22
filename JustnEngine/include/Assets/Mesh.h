#pragma once
#include "Assets\Asset.h"

#include <vector>
#include <iostream>
#include <string>

#include "gl_core_4_4.h"
#include "Assets\Material.h"
#include "Assets\Assetloader.h" //Change to manager

#include "Components\Transform.h"
#include "Cameras\Camera.h"

class VertexArrayObject;
class Shader;
class Material;
class FBXMeshNode;
class Transform;
class Camera;
class Component;

class Mesh : public Asset, public Component
{
public:
	Mesh();
	~Mesh();

	void LoadFile(std::string fileName);
	void LoadFBX(std::string fileName);

	void Update();
	void Render(Transform transform, Camera camera, std::vector<Light> lights, int shadowMap, bool setUniforms);

	void SetShader(Shader* shader);
	void SetMaterial(Material* material);

	Shader* GetShader() const { return m_pShader; }
	Material* GetMaterial() const { return m_pMaterial; }

private:

	void onBind() override;
	void onUnbind() override;

	void BuildRenderDataFromLoaderNode(VertexArrayObject** pRenderData, FBXMeshNode* pMesh);

	template<typename T>
	void BuildMaterialFromLoaderNode(Material** pMaterial, T* pLoaderMaterial)
	{
		m_pAssetManager->CreateMaterial(GetFileName());
		*pMaterial = m_pAssetManager->GetAsset<Material>(GetFileName());

		(*pMaterial)->InitializeFromLoaderMaterial(pLoaderMaterial);

	}
	int m_specularPower;

	VertexArrayObject* m_pRenderObject;
	Shader* m_pShader;
	Material* m_pMaterial;

	std::vector<Mesh*> m_internalMeshes;

};

