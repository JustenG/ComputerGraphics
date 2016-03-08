#include "Rendering\VertexArrayObject.h"

#include <vector>

VertexArrayObject::VertexArrayObject()
{

}


VertexArrayObject::~VertexArrayObject()
{
}

void VertexArrayObject::GenerateBuffer(GLuint &data)
{
	glGenVertexArrays(1, &data);
}

void VertexArrayObject::UnbindBuffer()
{
	glBindVertexArray(0);
}

void VertexArrayObject::BindBuffer(GLuint data)
{
	glBindVertexArray(data);
}

void VertexArrayObject::DeleteBuffers(GLuint VAO, GLuint VBO, GLuint IBO)
{
	glDeleteVertexArrays(1, &VAO);
	m_VertexBuffer->DeleteBuffers(VBO);
	m_IndexBuffer->DeleteBuffers(IBO);
}

template<>
void VertexArrayObject::SetUpAttributes<FBXVertex>()
{
	glEnableVertexAttribArray(0); //position
	glEnableVertexAttribArray(1); //normal data
	glEnableVertexAttribArray(2); //colour data
	glEnableVertexAttribArray(3); //texcoord1 data
	glEnableVertexAttribArray(4); //texcoord2 data
	glEnableVertexAttribArray(5); //tangent data
	glEnableVertexAttribArray(6); //binormal data
	glEnableVertexAttribArray(7); //indicies data
	glEnableVertexAttribArray(8); //weights data

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::PositionOffset);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::NormalOffset);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::ColourOffset);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::TexCoord1Offset);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::TexCoord2Offset);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::TangentOffset);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::BiNormalOffset);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::IndicesOffset);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (void*)FBXVertex::Offsets::WeightsOffset);
}

void VertexArrayObject::DrawObject(std::vector<GLuint> IBO_Data)
{
	glDrawElements(GL_TRIANGLES, (GLuint)IBO_Data.size(), GL_UNSIGNED_INT, 0);
}


