#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "gl_core_4_4.h"

class Component;

class Shader;
class Material;
class Mesh;
class Transform;
class Camera;
class Light;

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	~MeshRenderer();

	void Update();
	void Render(Transform transform, Camera camera, std::vector<Light> lights, int shadowMap, bool setUniforms = true);
	void Render(Light light, bool setUniforms = true);

	void SetShader(Shader* shader);
	void SetMaterial(Material* material);
	void SetMesh(Mesh* mesh);

	Shader* GetShader() const { return m_pShader; }
	Material* GetMaterial() const { return m_pMaterial; }

private:

	void Bind();
	void Unbind();

	int m_specularPower;

	Mesh* m_pMesh;
	Shader* m_pShader;
	Material* m_pMaterial;


};

