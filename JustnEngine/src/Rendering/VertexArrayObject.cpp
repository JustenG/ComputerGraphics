#include "Rendering\VertexArrayObject.h"

#include <vector>

VertexArrayObject::VertexArrayObject()
{
}


VertexArrayObject::~VertexArrayObject()
{

}

void VertexArrayObject::GenerateBuffer(GLuint* data)
{
	glGenVertexArrays(1, data);
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(m_pData[0]);
	m_VertexBuffer->Bind(m_pData[1]);
	m_IndexBuffer->Bind(m_pData[2]);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
	m_VertexBuffer->Unbind();
	m_IndexBuffer->Unbind();
}

void VertexArrayObject::BindVAO(GLuint data)
{
	glBindVertexArray(data);
}
void VertexArrayObject::UnbindVAO()
{
	glBindVertexArray(0);
}


void VertexArrayObject::DeleteBuffers(GLuint VAO, GLuint VBO, GLuint IBO)
{
	glDeleteVertexArrays(1, &VAO);
	m_VertexBuffer->DeleteBuffers(VBO);
	m_IndexBuffer->DeleteBuffers(IBO);

	delete m_IndexBuffer;
	delete m_VertexBuffer;
	delete m_pData;
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

void VertexArrayObject::DrawObject()
{
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetBufferSize(), GL_UNSIGNED_INT, 0);
}


