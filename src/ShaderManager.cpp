#include "ShaderManager.h"

std::map<std::string, Shader> ShaderManager::shadersResource;

Shader ShaderManager::GetShader(std::string name)
{
	return shadersResource[name];
}

Shader ShaderManager::LoadShaders(std::string vertexFile, std::string fragmentFile, std::string name)
{
	return shadersResource[name] = LoadShaderCode(vertexFile, fragmentFile);
}

void ShaderManager::FreeShaders()
{
	for (auto const& iter : shadersResource)
	{
		glDeleteProgram(iter.second.m_ID);
	}
}

Shader ShaderManager::LoadShaderCode(std::string vertexFile, std::string fragmentFile)
{
	FileReader::LoadShaderFromFile(vertexFile, fragmentFile, m_vertexCode, m_fragmentCode);
	return Shader(m_vertexCode, m_fragmentCode);
}