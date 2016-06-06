#include "Rendering\VertexBuffer.h"
//#include "Rendering\Vertex.h"

VertexBuffer::VertexBuffer()
{
}


VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::GenerateBuffer(GLuint* data)
{
	glGenBuffers(1, data);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Bind(GLuint data)
{
	glBindBuffer(GL_ARRAY_BUFFER, data);
}

void VertexBuffer::DeleteBuffers(GLuint VBO)
{
	glDeleteBuffers(1, &VBO);
}
