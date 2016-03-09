#include "Rendering\IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
}


IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::GenerateBuffer(GLuint &data)
{
	glGenBuffers(1, &data);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Bind(GLuint data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data);
}

void IndexBuffer::BindBuffer(GLuint data, GLuint size, GLuint* bufferData)
{
	m_IBO_Data = bufferData;
	Bind(data);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), bufferData, GL_STATIC_DRAW);
}

GLuint* IndexBuffer::GetBufferData()
{
	return m_IBO_Data;
}

void IndexBuffer::DeleteBuffers(GLuint IBO)
{
	glDeleteBuffers(1, &IBO);
}

GLuint* IndexBuffer::GenerateGridIndex(GLuint rows, GLuint cols)
{
	//Calculate grid index buffer
	//--------------------------------------------------------------------------------------------------------
	// defining index count based off quad count (2 triangles per quad)
	GLuint* AUIIndices = new GLuint[(rows - 1) * (cols - 1) * 6];
	GLuint index = 0;
	for (GLuint r = 0; r < (rows - 1); ++r)
	{
		for (GLuint c = 0; c < (cols - 1); ++c)
		{
			// triangle 1
			AUIIndices[index++] = r * cols + c;
			AUIIndices[index++] = (r + 1) * cols + c;
			AUIIndices[index++] = (r + 1) * cols + (c + 1);
			// triangle 2
			AUIIndices[index++] = r * cols + c;
			AUIIndices[index++] = (r + 1) * cols + (c + 1);
			AUIIndices[index++] = r * cols + (c + 1);
		}
	}

	return AUIIndices;
	//--------------------------------------------------------------------------------------------------------
}
