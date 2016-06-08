#include "Assets\Mesh.h"

#ifdef FBX_SUPPORTED
#include <FBXFile.h>
#endif

#include "gl_core_4_4.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Rendering\VertexArrayObject.h"
#include "Assets\Shader.h"
#include "Components\Camera.h"
#include "Components\Light.h"

Mesh::Mesh()
{
	m_pMaterial = nullptr;
	m_pRenderObject = new VertexArrayObject();
}

Mesh::~Mesh()
{
	delete m_pRenderObject;
}

void Mesh::Update()
{

}

void Mesh::onBind()
{
	m_pRenderObject->Bind();
}

void Mesh::onUnbind()
{
	m_pRenderObject->Unbind();
}


void Mesh::Render()
{
	Bind();
	m_pRenderObject->DrawObject();
	Unbind();
}

#ifdef FBX_SUPPORTED
void Mesh::BuildRenderDataFromLoaderNode(FBXMeshNode* pMesh)
{
	assert(pMesh);

	m_pRenderObject->CreateVAO<FBXVertex>(pMesh->m_vertices.size(), pMesh->m_indices.size(), pMesh->m_vertices.data(), pMesh->m_indices.data());
}
#endif

void Mesh::BuildRenderDataFromLoaderNode(GLuint vertexCount, GLuint indicesCount, Vertex* vertexData, GLuint* indicesData)
{
	m_pRenderObject->CreateVAO<Vertex>(vertexCount, indicesCount, vertexData, indicesData);
}
