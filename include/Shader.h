#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <../glm/glm.hpp>
#include <../glm/gtc/matrix_transform.hpp>
#include <../glm/gtc/type_ptr.hpp>

class Shader
{
private:
    // MEMBER VARIABLES
    std::string m_fragmentCode;
    std::string m_vertexCode;
    unsigned int m_ID;
public:
    Shader(std::string&, std::string&);
    ~Shader();

    void ActivateShader();
    void DeactivateShader();
    // UTILITY FUNCTIONS (MATH-RELATED)
    // void SetInt(const std::string&, int value) const;
    // void SetFloat(const std::string&, float value) const;
    // void SetVector2f(const std::string&, glm::vec2) const;
    // void SetVector3f(const std::string&, glm::vec3) const;
    // void SetVector4f(const std::string&, glm::vec4) const;
    // void SetMatrix4f(const std::string&, glm::mat4) const;

private:
    // UTILITY FUNCTIONS
    void CheckCompileErrors(unsigned int, std::string);
    void CheckLinkingErrors();
    // HANDLE SHADER CREATION AND COMPLIATION PROCESS
    void CompileShaders();
};

#endif // SHADER_H