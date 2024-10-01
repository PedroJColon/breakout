#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<std::string, Shader> ResourceManager::shaderResource;
std::map<std::string, Texture2D> ResourceManager::textureResource;

Texture2D ResourceManager::GetTexture(std::string name)
{
	return textureResource[name];
}

Texture2D ResourceManager::LoadTexture(const std::string& filePath, std::string name, bool alpha)
{
	return textureResource[name] = LoadTextureFromFile(filePath, alpha);
}

Shader ResourceManager::GetShader(std::string name)
{
	return shaderResource[name];
}

Shader ResourceManager::LoadShaders(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath, std::string name)
{
	return shaderResource[name] = LoadShaderFromFile(vertexPath, fragmentPath, geometryPath);
}

void ResourceManager::FreeResources()
{
	for	(auto const& iter : shaderResource)
	{
		glDeleteProgram(iter.second.m_ID);
	}
	for (auto const& iter : textureResource)
	{
		glDeleteProgram(iter.second.m_ID);
	}
}

Shader ResourceManager::LoadShaderFromFile(const std::string& vertexFile, const std::string& fragmentFile, const std::string& geometryFile)
{
    std::ifstream vertexFileStream;
    std::ifstream fragmentFileStream;

    std::string vertexCode, fragmentCode, geometryCode;

    // Ifstream can throw exception
    vertexFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Open our shader files and have them be read into our file streams
        vertexFileStream.open(vertexFile.c_str());
        fragmentFileStream.open(fragmentFile.c_str());
        // create string stream variables to read each line buffer to get our shader code
        std::stringstream vertexStringStream, fragmentStringStream;
        // Read file buffer and output into string streams
        vertexStringStream << vertexFileStream.rdbuf();
        fragmentStringStream << fragmentFileStream.rdbuf();
        // Once we are done reading our file, close it!
        vertexFileStream.close();
        fragmentFileStream.close();
        // Convert our string stream into String class
        vertexCode = vertexStringStream.str();
        fragmentCode = fragmentStringStream.str();

        if (!geometryFile.empty())
        {
            // TODO: Read File buffer for geometry shader
        }

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_READ" << std::endl;
    }

    Shader shader;
    shader.CompileShaders(vertexCode, fragmentCode, geometryCode);
	return shader; // return our newly complied shader
}

Texture2D ResourceManager::LoadTextureFromFile(std::string filePath, bool alpha)
{
    Texture2D newTexture;
    if (alpha) // If image has an alpha, ensure that the texture will use RGBA instead of RGB!
    {
        newTexture.m_imageFormat = GL_RGBA;
        newTexture.m_internalFormat = GL_RGBA;
    }
    int width, height, nrChannels; // set the variables to pass in for stbi_load
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0); // load file using stbi library
    if (data)
    {
        std::cout << "IMAGE::SUCCESSFULLY::READ\n" << std::endl;
    }
    else
    {
        std::cout << "IMAGE::FAILURE::NOT_READ::" << stbi_failure_reason() << "\n" << std::endl;
    }
    // Magic Texture Generation!
    newTexture.GenerateTexture(width, height, data);
    // Free data after we have used it - Goodbye Data!
    stbi_image_free(data);
    return newTexture; // Return our newly generated texture
}
