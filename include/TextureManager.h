#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <glad/glad.h>

#include <map>
#include <string>

#include "FileReader.h"
#include "Texture2D.h"

class TextureManager
{
public:
	// Holds all texture resources
	static std::map<std::string, Texture2D> textureResource;
	// Get specified Texture from name given
	static Texture2D GetTexture(std::string);
	// Load and Create Texture
	static Texture2D LoadTexture(std::string, std::string, bool);
	// Destroy Textures once no longer needed
	static void FreeTextures();

private:
	// Empty Constructor - Since everything is static, we don't need to create object. Mainly there to keep compiler happy :)
	TextureManager() {};
	// Load Texture from Image data gathered
	static Texture2D LoadTextureFromData(std::string, bool);
};

#endif // !TEXTUREMANAGER_H