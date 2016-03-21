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

	bool Create();
	void Destroy();

	GLuint GetId() const { return m_fboId; }
	const Texture& GetTexture() const { return m_fboTexture; }
	const Texture& GetDepthBufferId() const { return m_fboDepthTex; }
	const glm::ivec2& GetSize() const { return m_fboSize; }
	const Shader& GetShaderProgram() { return m_fboProgram; }

private:

	GLuint m_fboId = 0;
	glm::ivec2 m_fboSize;
	Texture m_fboTexture;
	Texture m_fboDepthTex;
	bool m_createColorBuffer;
	bool m_createDepthBuffer;
	Shader m_fboProgram; // Everything in this RenderPass will be rendered with the Program if it is set.

};
