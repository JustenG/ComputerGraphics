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
	void CreateVAO(GLuint &VAO, GLuint &VBO, GLuint &IBO, GLuint VBO_Size, GLuint IBO_Size, T* VBO_Data, GLuint* IBO_Data);
	template<typename T>
	void CreateVAO(GLuint* DataID, GLuint VBO_Size, GLuint IBO_Size, T* VBO_Data, GLuint* IBO_Data);

	void GenerateBuffer(GLuint &data);
	void BindBuffer(GLuint data);
	void UnbindBuffer();
	void DeleteBuffers(GLuint VAO, GLuint VBO, GLuint IBO);

	template<typename T>
	void SetUpAttributes();

	void DrawObject(std::vector<GLuint> IBO_Data);

private:

	GLuint m_Rows;
	GLuint m_Cols;
	
	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;

};

template<>
void VertexArrayObject::SetUpAttributes<FBXVertex>();

//template<>
//void VertexArrayObject::SetUpAttributes<FBXVertex>();

template<typename T>
void VertexArrayObject::CreateVAO(GLuint &VAO, GLuint &VBO, GLuint &IBO, GLuint VBO_Size, GLuint IBO_Size, T* VBO_Data, GLuint* IBO_Data)
{
	m_VertexBuffer = new VertexBuffer();
	m_IndexBuffer = new IndexBuffer();

	GenerateBuffer(VAO);
	BindBuffer(VAO);

	m_VertexBuffer->GenerateBuffer(VBO);
	m_IndexBuffer->GenerateBuffer(IBO);


	m_VertexBuffer->BindBuffer<T>(VBO, VBO_Size, VBO_Data);
	m_IndexBuffer->BindBuffer(IBO, IBO_Size, IBO_Data);

	SetUpAttributes<T>();

	UnbindBuffer();
	m_VertexBuffer->UnbindBuffer();
	m_IndexBuffer->UnbindBuffer();
}

template<typename T>
void VertexArrayObject::CreateVAO(GLuint* DataID, GLuint VBO_Size, GLuint IBO_Size, T* VBO_Data, GLuint* IBO_Data)
{
	m_VertexBuffer = new VertexBuffer();
	m_IndexBuffer = new IndexBuffer();

	GenerateBuffer(DataID[0]);
	BindBuffer(DataID[0]);

	m_VertexBuffer->GenerateBuffer(DataID[1]);
	m_IndexBuffer->GenerateBuffer(DataID[2]);


	m_VertexBuffer->BindBuffer<T>(DataID[1], VBO_Size, VBO_Data);
	m_IndexBuffer->BindBuffer(DataID[2], IBO_Size, IBO_Data);

	SetUpAttributes<T>();

	UnbindBuffer();
	m_VertexBuffer->UnbindBuffer();
	m_IndexBuffer->UnbindBuffer();
}



