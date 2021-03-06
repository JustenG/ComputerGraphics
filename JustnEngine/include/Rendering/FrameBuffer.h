#pragma once

#include "gl_core_4_4.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Assets/Shader.h"
#include "Assets/Texture.h"

class Camera;

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void Unbind();

	bool CreateBuffer(bool colour, bool depth);
	void Reset(glm::ivec2 size);
	void Destroy();
	void SetShaderProgram(Shader* shader) { m_fboProgram = shader; }

	GLuint GetId() const { return m_fboId; }
	const glm::ivec2& GetSize() const { return m_fboSize; }
	Texture* GetTexture() const { return m_fboTexture; }
	Texture* GetDepthBuffer() const { return m_fboDepthTex; }
	Shader* GetShader() { return m_fboProgram; }

private:

	GLuint m_fboId = 0;
	glm::ivec2 m_fboSize;
	Texture* m_fboTexture;
	Texture* m_fboDepthTex;
	Shader* m_fboProgram; // Everything in this RenderPass will be rendered with the Program if it is set.

};
