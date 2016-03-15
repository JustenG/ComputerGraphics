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



//Vertex* VertexBuffer::GenerateGridVertex(GLuint rows, GLuint cols)
//{
	//Calculate grid vertices buffer
	//--------------------------------------------------------------------------------------------------------
	//Vertex* AOVertices = new Vertex[rows * cols];
	//for (GLuint r = 0; r < rows; ++r)
	//{
	//	for (GLuint c = 0; c < cols; ++c)
	//	{
	//		AOVertices[r * cols + c].position = glm::vec4((float)c, 0, (float)r, 1);

	//		// create some arbitrary colour based off something
	//		// that might not be related to tiling a texture
	//		glm::vec3 colour = glm::vec3(sinf((c / (float)(cols - 1)) *	(r / (float)(rows - 1))));

	//		AOVertices[r * cols + c].colour = glm::vec4(colour, 1);
	//	}
	//}

	//return AOVertices;
	//--------------------------------------------------------------------------------------------------------
//}
