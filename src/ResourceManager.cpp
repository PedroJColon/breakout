#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader ResourceManager::LoadShader(std::string &vertexFile, std::string &fragmentFile, std::string name)
{
    return shaders[name] = LoadShaderFromFile(vertexFile, fragmentFile);
}

Shader ResourceManager::GetShader(std::string name)
{
    return shaders[name];
}

Texture2D ResourceManager::LoadTexture(std::string &textureFile, bool alpha, std::string name)
{
    return textures[name] = LoadTextureFromFile(textureFile, alpha);
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return textures[name];
}

void ResourceManager::Free()
{
    for (auto const& iter : shaders)
    {
        glDeleteProgram(iter.second.m_ID);
    }
    for (auto const& iter : textures)
    {
        glDeleteProgram(iter.second.m_ID);
    }
       
}

Shader ResourceManager::LoadShaderFromFile(std::string &vertexFile, std::string &fragmentFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    try
    {
        std::ifstream vertexFileStream(vertexFile);
        std::ifstream fragmentFileStream(fragmentFile);
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexFileStream.rdbuf();
        fragmentStream << fragmentFileStream.rdbuf();

        vertexFileStream.close();
        fragmentFileStream.close();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
        
    }
    catch(std::exception e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_READ" << std::endl;  
    }

    Shader shader;
    shader.CompileShaders(vertexCode, fragmentCode);

    return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(std::string &textureFile, bool alpha)
{
    Texture2D texture;
    if (alpha)
    {
        // texture.Internal_Format = GL_RGBA;
        // texture.Image_Format = GL_RGBA;
    }
    int width, height, nrChannels;
    const char* file = textureFile.c_str();
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data)
    {
        texture.Generate(width, height, data);
    }
    else
    {
        std::cout << "Unable to Load Texture\n" << std::endl;
    }
    
    stbi_image_free(data);
    return texture;
}
