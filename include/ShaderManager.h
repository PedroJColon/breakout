#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

// Glad ulitly to handle GL calls
#include <glad/glad.h>

// 
#include <map>
#include <string>

// CLASS INCLUDES
#include "FileReader.h"
#include "Shader.h"


// NOTE: Geometry Shader file support? Will Keep this in mind

// Handles Management of Shaders Creation, Loading, and Destruction
class ShaderManager
{
private:
	std::string m_vertexCode;
	std::string m_fragmentCode;

public: 
	// Store all shaders into this static hash map
	static std::map<std::string, Shader> shadersResource;
	// Get specific shader name within hash map
	Shader GetShader(std::string);
	// Public Function to Load Shaders into shadersResource
	Shader LoadShaders(std::string, std::string, std::string);
	// Once program is done, Free shader resources
	static void FreeShaders();

private:
	// Load ShaderCode to construct and return Shader object
	Shader LoadShaderCode(std::string, std::string);
};

#endif // !SHADERMANAGER_H