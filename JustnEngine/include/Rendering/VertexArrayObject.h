#pragma once
#include <vector>

#include "gl_core_4_4.h"
#include "FBXFile.h"

#include "Rendering\VertexBuffer.h"
#include "Rendering\IndexBuffer.h"	

class VertexBuffer;
class IndexBuffer;

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();

	template<typename T>
	void CreateVAO(GLuint VBO_Size, GLuint IBO_Size, T* VBO_Data, GLuint* IBO_Data);

	void GenerateBuffer(GLuint* data);
	void Bind();
	void BindVAO(GLuint data);
	void Unbind();
	void UnbindVAO();
	void DeleteBuffers(GLuint VAO, GLuint VBO, GLuint IBO);

	template<typename T>
	void SetUpAttributes();

	void DrawObject();

private:

	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;

	GLuint m_pData[3];
};

template<>
void VertexArrayObject::SetUpAttributes<FBXVertex>();

template<typename T>
void VertexArrayObject::CreateVAO(GLuint VBO_Size, GLuint IBO_Size, T* VBO_Data, GLuint* IBO_Data)
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



