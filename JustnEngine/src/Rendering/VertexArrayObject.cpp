#include "Rendering\VertexArrayObject.h"
#include "Rendering\Vertex.h"
#include "all_includes.h"


#pragma region Locals
VertexArrayObject::VertexArrayObject() 
{}
VertexArrayObject::~VertexArrayObject()
{}

void VertexArrayObject::GenerateBuffer(uint* data)
{
	glGenVertexArrays(1, data);
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(m_pData[0]);
	m_VertexBuffer->Bind(m_pData[1]);
	m_IndexBuffer->Bind(m_pData[2]);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
	m_VertexBuffer->Unbind();
	m_IndexBuffer->Unbind();
}

void VertexArrayObject::BindVAO(uint data)
{
	glBindVertexArray(data);
}
void VertexArrayObject::UnbindVAO()
{
	glBindVertexArray(0);
}

void VertexArrayObject::DeleteBuffers(uint VAO, uint VBO, uint IBO)
{
	glDeleteVertexArrays(1, &VAO);
	m_VertexBuffer->DeleteBuffers(VBO);
	m_IndexBuffer->DeleteBuffers(IBO);

	delete m_IndexBuffer;
	delete m_VertexBuffer;
}

void VertexArrayObject::DrawObject()
{
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetBufferSize(), GL_UNSIGNED_INT, 0);
}
#pragma endregion

#pragma region Globals
void PushAttribute(uint attributeSize, uint vertexSize, size_t offset)
{
	glEnableVertexAttribArray(VAO_NUM_ATTRIBUTES);
	glVertexAttribPointer(VAO_NUM_ATTRIBUTES, attributeSize, GL_FLOAT, GL_FALSE, vertexSize, (void*)offset);

	VAO_NUM_ATTRIBUTES++;
	VAO_NUM_FLOATS += attributeSize;
}

void ClearVAOMetadata()
{
	VAO_NUM_FLOATS = 0;
	VAO_NUM_ATTRIBUTES = 0;
}
#pragma endregion

#pragma region Templates
template<>
void VertexArrayObject::SetUpAttributes<FBXVertex>()
{
	ClearVAOMetadata();
	subscribe(FBXVertex, position);
	subscribe(FBXVertex, normal);
	subscribe(FBXVertex, colour);
	subscribe(FBXVertex, texCoord1);
	subscribe(FBXVertex, texCoord2);
	subscribe(FBXVertex, tangent);
	subscribe(FBXVertex, binormal);
	subscribe(FBXVertex, indices);
	subscribe(FBXVertex, weights);
}

template<>
void VertexArrayObject::SetUpAttributes<Vertex>()
{
	ClearVAOMetadata();
	subscribe(Vertex, position);
	subscribe(Vertex, colour);
	subscribe(Vertex, normal);
	subscribe(Vertex, texCoord);
}
#pragma endregion

