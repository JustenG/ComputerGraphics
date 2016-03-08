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
	void UnbindBuffer();
	void BindBuffer(GLuint data, GLuint size, GLuint* bufferData);

	void DeleteBuffers(GLuint IBO);

	GLuint* GenerateGridIndex(GLuint rows, GLuint cols);

private:

	GLuint m_IBO;

};

