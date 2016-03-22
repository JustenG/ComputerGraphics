#pragma once
#include <vector>
#include "gl_core_4_4.h"
#include "FBXFile.h"

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

	template <typename T>
	void SetAttributes(GLuint textureOffset, GLuint noramlOffset, GLuint tangent, GLuint weight, GLuint indices);

private:

	GLuint m_VBO;

};

template <typename T>
void VertexBuffer::BindBuffer(GLuint data, GLuint size, T* bufferData)
{
	glBindBuffer(GL_ARRAY_BUFFER, data);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), bufferData, GL_STATIC_DRAW);
}

template <typename T>
void VertexBuffer::SetAttributes(GLuint textureOffset, GLuint noramlOffset, GLuint tangent, GLuint weight, GLuint indices)
{
	glEnableVertexAttribArray(0); //Pos
	glEnableVertexAttribArray(1); //Texture
	glEnableVertexAttribArray(2); //Normal
	glEnableVertexAttribArray(3); //tangents
	glEnableVertexAttribArray(4); //weights
	glEnableVertexAttribArray(5); //indices 

	//Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(T), 0);

	//Texture
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)textureOffset);

	//Normal
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(T), (void*)noramlOffset);

	//tangents
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_TRUE, sizeof(T), (void*)tangent);

	//weights
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)weight);
	
	//indices
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)indices);


}
