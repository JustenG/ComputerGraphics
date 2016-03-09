#pragma once
#include <vector>
#include "gl_core_4_4.h"
#include "FBXFile.h"

class Vertex;

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void GenerateBuffer(GLuint &data);
	void Unbind();
	void Bind(GLuint data);
	void BindBuffer(GLuint data, GLuint size, GLuint* bufferData);

	void DeleteBuffers(GLuint IBO);

	GLuint* GetBufferData();

	GLuint* GenerateGridIndex(GLuint rows, GLuint cols);

private:

	GLuint m_IBO;
	GLuint* m_IBO_Data;
};

