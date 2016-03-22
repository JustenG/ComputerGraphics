#include "Assets\Shader.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "FBXFile.h"
#include "stb_image.h"
#include "Assets\Material.h"

Shader::Shader()
{


}

Shader::~Shader()
{

}

void Shader::onBind()
{
	glUseProgram(m_ProgramID);
}

void Shader::onUnbind()
{
	glUseProgram(0);
}

void Shader::LoadShader(std::string vertexPath, std::string fragmentPath)
{
	// 1. Retrieve the vertex/fragment source code from filePath

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	// Convert string into char array
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();
	
	// 2. Compile shaders

	int success = GL_FALSE;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&vShaderCode, 0);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char**)&fShaderCode, 0);
	glCompileShader(fragmentShader);

	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, vertexShader);
	glAttachShader(m_ProgramID, fragmentShader);

	//Setup Attribute Bindings
	glBindAttribLocation(m_ProgramID, 0, "Position");
	glBindAttribLocation(m_ProgramID, 1, "Normal");
	glBindAttribLocation(m_ProgramID, 2, "Colour");
	glBindAttribLocation(m_ProgramID, 3, "TexCoords");
	glBindAttribLocation(m_ProgramID, 4, "TexCoords2");
	glBindAttribLocation(m_ProgramID, 5, "Tangent");
	glBindAttribLocation(m_ProgramID, 6, "Binormal");
	glBindAttribLocation(m_ProgramID, 7, "Indices");
	glBindAttribLocation(m_ProgramID, 8, "Weights");

	glLinkProgram(m_ProgramID);

	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(m_ProgramID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	Bind();
	//Prepare Shade rUniforms
	m_shaderUniforms[SupportedShaderUniforms::Projection] = glGetUniformLocation(m_ProgramID, "projection");
	m_shaderUniforms[SupportedShaderUniforms::View] = glGetUniformLocation(m_ProgramID, "view");
	m_shaderUniforms[SupportedShaderUniforms::Model] = glGetUniformLocation(m_ProgramID, "model");
	m_shaderUniforms[SupportedShaderUniforms::ProjectionView] = glGetUniformLocation(m_ProgramID, "projectionView");
	m_shaderUniforms[SupportedShaderUniforms::ProjectionViewModel] = glGetUniformLocation(m_ProgramID, "projectionViewModel");
	m_shaderUniforms[SupportedShaderUniforms::CameraPosition] = glGetUniformLocation(m_ProgramID, "cameraPosition");
	//Setup Texture Locations
	m_shaderUniforms[SupportedShaderUniforms::DiffuseTexture] = glGetUniformLocation(m_ProgramID, "DiffuseTexture");
	m_shaderUniforms[SupportedShaderUniforms::AmbientTexture] = glGetUniformLocation(m_ProgramID, "AmbientTexture");
	m_shaderUniforms[SupportedShaderUniforms::GlowTexture] = glGetUniformLocation(m_ProgramID, "GlowTexture");
	m_shaderUniforms[SupportedShaderUniforms::SpecularTexture] = glGetUniformLocation(m_ProgramID, "SpecularTexture");
	m_shaderUniforms[SupportedShaderUniforms::GlossTexture] = glGetUniformLocation(m_ProgramID, "GlossTexture");
	m_shaderUniforms[SupportedShaderUniforms::NormalTexture] = glGetUniformLocation(m_ProgramID, "NormalTexture");
	m_shaderUniforms[SupportedShaderUniforms::AlphaTexture] = glGetUniformLocation(m_ProgramID, "AlphaTexture");
	m_shaderUniforms[SupportedShaderUniforms::DisplacementTexture] = glGetUniformLocation(m_ProgramID, "DisplacementTexture");

	glUniform1i(m_shaderUniforms[SupportedShaderUniforms::DiffuseTexture], Material::DiffuseTexture);
	glUniform1i(m_shaderUniforms[SupportedShaderUniforms::AmbientTexture], Material::AmbientTexture);
	glUniform1i(m_shaderUniforms[SupportedShaderUniforms::GlowTexture], Material::GlowTexture);
	glUniform1i(m_shaderUniforms[SupportedShaderUniforms::SpecularTexture], Material::SpecularTexture);
	glUniform1i(m_shaderUniforms[SupportedShaderUniforms::GlossTexture], Material::GlossTexture);
	glUniform1i(m_shaderUniforms[SupportedShaderUniforms::NormalTexture], Material::NormalTexture);
	glUniform1i(m_shaderUniforms[SupportedShaderUniforms::AlphaTexture], Material::AlphaTexture);
	glUniform1i(m_shaderUniforms[SupportedShaderUniforms::DisplacementTexture], Material::DisplacementTexture);

	Unbind();
}

void Shader::SetProjectionUniform(const glm::mat4& mat)
{
	Bind();
	glUniformMatrix4fv(m_shaderUniforms[SupportedShaderUniforms::Projection], 1, GL_FALSE, glm::value_ptr(mat));
	Unbind();
}

void Shader::SetViewUniform(const glm::mat4& mat)
{
	Bind();
	glUniformMatrix4fv(m_shaderUniforms[SupportedShaderUniforms::View], 1, GL_FALSE, glm::value_ptr(mat));
	Unbind();
}

void Shader::SetModelUniform(const glm::mat4& mat)
{
	Bind();
	glUniformMatrix4fv(m_shaderUniforms[SupportedShaderUniforms::Model], 1, GL_FALSE, glm::value_ptr(mat));
	Unbind();
}

void Shader::SetProjectionViewUniform(const glm::mat4& mat)
{
	Bind();
	glUniformMatrix4fv(m_shaderUniforms[SupportedShaderUniforms::ProjectionView], 1, GL_FALSE, glm::value_ptr(mat));
	Unbind();
}

void Shader::SetProjectionViewModelUniform(const glm::mat4& mat)
{
	Bind();
	glUniformMatrix4fv(m_shaderUniforms[SupportedShaderUniforms::ProjectionViewModel], 1, GL_FALSE, glm::value_ptr(mat));
	Unbind();
}

void Shader::SetCameraPositionUniform(const glm::vec3& vec)
{
	Bind();
	glUniform3fv(m_shaderUniforms[SupportedShaderUniforms::CameraPosition], 1, glm::value_ptr(vec));
	Unbind();
}


void Shader::SetUniform(int uniformID, float value)
{
	Bind();
	glUniform1f(uniformID, value);
	Unbind();
}

void Shader::SetUniform(int uniformID, int value)
{
	Bind();
	glUniform1i(uniformID, value);
	Unbind();
}

void Shader::SetUniform(int uniformID, glm::vec2 value)
{
	Bind();
	glUniform2fv(uniformID, 1, glm::value_ptr(value));
	Unbind();
}

void Shader::SetUniform(int uniformID, glm::vec3 value)
{
	Bind();
	glUniform3fv(uniformID, 1, glm::value_ptr(value));
	Unbind();
}

void Shader::SetUniform(int uniformID, glm::vec4 value)
{

	Bind();
	glUniform4fv(uniformID, 1, glm::value_ptr(value));
	Unbind();
}

void Shader::SetUniform(int uniformID, glm::mat4 value)
{
	Bind();
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(value));
	Unbind();
}
