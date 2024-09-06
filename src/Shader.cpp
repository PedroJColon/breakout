#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::ActivateShader()
{
    glUseProgram(m_ID);
}

void Shader::DeactivateShader()
{
    glUseProgram(0);
}


void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << type <<"::COMPLIATION_FAILE\n" << std::endl;
    }
}

void Shader::CheckLinkingErrors()
{
    int success;
    char infoLog[512];

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << std::endl;   
    }
    
}

void Shader::CompileShaders(std::string& shaderVertexCode, std::string& shaderFragmentCode)
{
    unsigned int vertex, fragment;

    const char* vertexCode = shaderVertexCode.c_str();
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    const char* fragmentCode = shaderFragmentCode.c_str();
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    CheckLinkingErrors();

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}