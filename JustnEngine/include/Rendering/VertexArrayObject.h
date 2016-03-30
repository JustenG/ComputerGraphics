#pragma once
#include <vector>

#include "global_includes.h"
#include "FBXFile.h"

#include "Rendering\VertexBuffer.h"
#include "Rendering\IndexBuffer.h"	

static uint VAO_NUM_FLOATS;
static uint VAO_NUM_ATTRIBUTES;

#define subscribe(vertex_t, attribute_name) \
{ \
	auto offset = ((size_t)&reinterpret_cast<char const volatile&>((((vertex_t*)0)->attribute_name))); \
	PushAttribute(sizeof(vertex_t::attribute_name) / sizeof(float), sizeof(vertex_t), offset);\
}

void PushAttribute(uint attributeSize, uint vertexSize, size_t offset);
void ClearVAOMetadata();
class VertexBuffer;
class IndexBuffer;

class VertexArrayObject
{
public:

	VertexArrayObject();
	~VertexArrayObject();

	template<typename T>
	void CreateVAO(uint VBO_Size, uint IBO_Size, T* VBO_Data, uint* IBO_Data);

	void GenerateBuffer(uint* data);
	void Bind();
	void BindVAO(uint data);
	void Unbind();
	void UnbindVAO();
	void DeleteBuffers(uint VAO, uint VBO, uint IBO);

	template<typename T>
	void SetUpAttributes();

	//void PushAttribute(uint attributeSize, uint vertexSize, size_t offset);

	void DrawObject();

private:

	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;

	uint m_pData[3];

	uint m_numAttributes;
};

template<typename T>
void VertexArrayObject::CreateVAO(uint VBO_Size, uint IBO_Size, T* VBO_Data, uint* IBO_Data)
{
	memset(m_pData, 0, 3);
	m_VertexBuffer = new VertexBuffer();
	m_IndexBuffer = new IndexBuffer();

	GenerateBuffer(&m_pData[0]);
	BindVAO(*m_pData);

	m_VertexBuffer->GenerateBuffer(&m_pData[1]);
	m_IndexBuffer->GenerateBuffer(&m_pData[2]);

	m_VertexBuffer->BindBuffer<T>(m_pData[1], VBO_Size, VBO_Data);
	m_IndexBuffer->BindBuffer(m_pData[2], IBO_Size, IBO_Data);

	SetUpAttributes<T>();

	UnbindVAO();
	m_VertexBuffer->Unbind();
	m_IndexBuffer->Unbind();
}



