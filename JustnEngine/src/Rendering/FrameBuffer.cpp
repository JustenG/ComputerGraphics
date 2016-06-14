#include "Rendering\FrameBuffer.h"
#include "all_includes.h"


FrameBuffer::FrameBuffer()
{
	m_fboTexture = new Texture();
	m_fboDepthTex = new Texture();
	m_fboProgram = nullptr;
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
	glViewport(0,0, m_fboSize.x, m_fboSize.y);

	m_fboTexture->Bind();
	m_fboDepthTex->Bind();

	glClearColor(0.2f, 0.2f, 0.2f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_fboTexture->Unbind();
	m_fboDepthTex->Unbind();
}

bool FrameBuffer::CreateBuffer(bool colour, bool depth)
{
	// setup framebuffer
	glGenFramebuffers(1, &m_fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	if (colour)
	{
		// Make the texture the FBO will render to.
		GLuint fboTextureId;
		glGenTextures(1, &fboTextureId);
		glBindTexture(GL_TEXTURE_2D, fboTextureId);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, m_fboSize.x, m_fboSize.y);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Attach the texture to the FBO
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fboTextureId, 0);

		// Let the FBO know which attachment to render to
		GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);

		// Save the texture to be used by following render passes.
		m_fboTexture->SetID(fboTextureId);
	}
	else
	{
		glDrawBuffer(GL_NONE);
	}

	if (depth)
	{
		// Create the depth buffer
		/*
		glGenRenderbuffers(1, &m_fboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, m_fboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_fboSize.x, m_fboSize.y);

		// Attach the depth buffer to the FBO
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_fboDepth);
		*/

		uint fboDepthId;
		glGenTextures(1, &fboDepthId);
		glBindTexture(GL_TEXTURE_2D, fboDepthId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, m_fboSize.x, m_fboSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, fboDepthId, 0);

		m_fboDepthTex->SetID(fboDepthId);

	}

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void FrameBuffer::Reset(ivec2 size)
{
	Destroy();
	glDeleteFramebuffers(1, &m_fboId);
	m_fboId = 0;
	m_fboSize = ivec2(size);
}

void FrameBuffer::Destroy()
{
	GLuint texId = m_fboTexture->GetID();
	GLuint depthTexId = m_fboDepthTex->GetID();
	if (texId) glDeleteTextures(1, &texId);
	if (depthTexId) glDeleteTextures(1, &depthTexId);
}
