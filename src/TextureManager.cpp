#include "TextureManager.h"

std::map<std::string, Texture2D> TextureManager::textureResource;

Texture2D TextureManager::GetTexture(std::string name)
{
	return textureResource[name];
}

Texture2D TextureManager::LoadTexture(std::string textureFile, std::string name, bool alpha)
{
	return textureResource[name] = LoadTextureFromData(textureFile, alpha); // Once we generate Texture from Data, send it to resource
}

void TextureManager::FreeTextures()
{
	// Iterate to textureResource
	for (auto const& iter : textureResource)
	{
		// Delete textures associated with their texture ID
		glDeleteTextures(1, &iter.second.m_ID);
	}
}

Texture2D TextureManager::LoadTextureFromData(std::string textureFile, bool alpha)
{
	// Set variables to be referenced from FileReader function
	int width, height, nrChannels;
	unsigned char* imageData = 0; // Init to zero for memory reasons
	FileReader::LoadImageFromFile(textureFile, alpha, width, height, nrChannels, imageData);
	Texture2D texture(width, height, imageData, alpha); // Generate Texture with the given information
	FileReader::FreeImageData(imageData); // Free the data once texture is generated
	return texture;
}