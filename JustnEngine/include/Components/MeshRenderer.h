#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "gl_core_4_4.h"

#include "Components\Component.h"

class Shader;
class Material;
class Mesh;
class Transform;
class Camera;
class Light;

class MeshRenderer : public Component<Transform>
{
public:
	MeshRenderer();
	~MeshRenderer();

	void Update();
	void Render(Camera camera, std::vector<Light> lights, int shadowMap);
	void Render(Light light);

	void SetShader(Shader* shader);
	void SetMaterial(Material* material);
	void SetMesh(Mesh* mesh);

	Shader* GetShader() const { return m_pShader; }
	Material* GetMaterial() const { return m_pMaterial; }

protected:

	void Bind();
	void Unbind();
	virtual void SetShaderUniforms();

	int m_specularPower = 8;

	Mesh* m_pMesh;
	Shader* m_pShader;
	Material* m_pMaterial;


};

