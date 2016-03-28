#pragma once
#include <vector>
#include "gl_core_4_4.h"
#include "FBXFile.h"
#include "Rendering\Vertex.h"

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void GenerateBuffer(GLuint* data);
	template<typename T>
	void BindBuffer(GLuint data, GLuint size, T* bufferData);
	void Bind(GLuint data);
	void Unbind();

	void DeleteBuffers(GLuint VBO);

private:

	GLuint m_VBO;

};

template <typename T>
void VertexBuffer::BindBuffer(GLuint data, GLuint size, T* bufferData)
{
	glBindBuffer(GL_ARRAY_BUFFER, data);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), bufferData, GL_STATIC_DRAW);
}