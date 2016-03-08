#include "Assets/Shader.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "FBXFile.h"
#include "stb_image.h"

Shader::Shader()
{


}

Shader::~Shader()
{

}

void Shader::LoadShader(const GLchar* vertexPath, const GLchar* fragmentPath)
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

	glUseProgram(m_ProgramID);
}
