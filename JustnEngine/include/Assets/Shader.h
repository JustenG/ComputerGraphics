#pragma once

#include "gl_core_4_4.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Shader
{
public:
	Shader();
	~Shader();

	void LoadShader(const GLchar* vertexPath, const GLchar* fragmentPath);

private:

	GLuint m_ProgramID;

};

