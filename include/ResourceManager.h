#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <glad/glad.h>

// INCLUDES
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// MY CLASS INCLUDES
#include "Shader.h"
#include "Texture2D.h"

class ResourceManager
{    
public:
    // ~ResourceManager();
    // Store Shader Resources
    static std::map<std::string, Shader> shaders;
    // Store Texture Resources
    static std::map<std::string, Texture2D> textures;
    static Shader LoadShader(std::string&, std::string&, std::string);
    static Shader GetShader(std::string);
    static Texture2D LoadTexture(std::string&, bool, std::string);
    static Texture2D GetTexture(std::string);

    static void Free();
private:
    ResourceManager();
    static Shader LoadShaderFromFile(std::string&, std::string&);
    static Texture2D LoadTextureFromFile(std::string&, bool);
};

#endif