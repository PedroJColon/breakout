#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

// Glad ulitly to handle GL calls
#include <glad/glad.h>

// STL helpers
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// CLASS INCLUDES
#include "Shader.h"
#include "Texture2D.h"


class ResourceManager
{
public:
	// Holds all texture resources
	static std::map<std::string, Texture2D> textureResource;
	// Store all shaders into this static hash map
	static std::map<std::string, Shader> shaderResource;


	// Get specified Texture from name given
	static Texture2D GetTexture(std::string);
	// Load and Create Texture
	static Texture2D LoadTexture(std::string, std::string, bool);
	// Get specific shader name within hash map
	static Shader GetShader(std::string);
	// Public Function to Load Shaders into shadersResource
	static Shader LoadShaders(std::string, std::string, std::string, std::string);
	// Once program is done, free all resources
	static void FreeResources();

private:
	ResourceManager() {};
	~ResourceManager() {};

	// Loads vertex and fragment shaders from the file given. Geometry shader support down the line?
	static Shader LoadShaderFromFile(std::string, std::string, std::string);
	// Loads Image from file given
	static Texture2D LoadTextureFromFile(std::string, bool);
};


#endif // !RESOURCEMANAGER_H
