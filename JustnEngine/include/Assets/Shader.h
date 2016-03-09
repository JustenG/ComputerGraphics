#pragma once
#include "Assets\Asset.h"

#include "gl_core_4_4.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Shader : public Asset
{
public:
	enum SupportedShaderUniforms
	{
		/*Common required transforms*/
		Projection,
		View,
		Model,
		ProjectionView,
		ProjectionViewModel,

		/*Texture Samplers*/
		DiffuseTexture,
		AmbientTexture,
		GlowTexture,
		SpecularTexture,
		GlossTexture,
		NormalTexture,
		AlphaTexture,
		DisplacementTexture,

		/*Total number of uniforms*/
		NUM_SUPPORTED_UNIFORMS
	};

	Shader();
	~Shader();

	void LoadShader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void SetProjectionUniform(const glm::mat4& mat);
	void SetViewUniform(const glm::mat4& mat);
	void SetModelUniform(const glm::mat4& mat);
	void SetProjectionViewUniform(const glm::mat4& mat);
	void SetProjectionViewModelUniform(const glm::mat4& mat);

	template<typename T>
	int SetUniform(std::string uniformName, T& value)
	{
		int iPos = -1;
		auto it = m_cachedShaderUniforms.find(uniformName);
		if (it == m_cachedShaderUniforms.end())
		{
			iPos = glGetUniformLocation(m_shaderID, uniformName.c_str());
			m_cachedShaderUniforms[uniformName] = iPos;
		}
		else
		{
			iPos = it->second;
		}

		SetUniform(iPos, value);
		return iPos;
	}

	void SetUniform(int uniformID, float value);
	void SetUniform(int uniformID, int value);
	void SetUniform(int uniformID, glm::vec2 value);
	void SetUniform(int uniformID, glm::vec3 value);
	void SetUniform(int uniformID, glm::vec4 value);
	void SetUniform(int uniformID, glm::mat4 value);

private:

	void onBind() override;
	void onUnbind() override;

	GLuint m_ProgramID;
	GLuint m_shaderUniforms[SupportedShaderUniforms::NUM_SUPPORTED_UNIFORMS];

};

