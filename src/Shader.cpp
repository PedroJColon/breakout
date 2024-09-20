#include "Shader.h"

Shader::Shader()
{
    m_ID = 0;
}

Shader::Shader(std::string& shaderVertexCode, std::string& shaderFragmentCode)
{
    //unsigned int vertex, fragment;

    //// Has to be converted to const char due to how GLAD glShaderSource works (Gives errors if we use string)
    //const char* vertexCode = shaderVertexCode.c_str();
    //// Compile our Vertex shader now
    //vertex = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertex, 1, &vertexCode, NULL);
    //glCompileShader(vertex);
    //CheckCompileErrors(vertex, "VERTEX");

    //// Has to be converted to const char due to how GLAD glShaderSource works (Gives errors if we use string)
    //const char* fragmentCode = shaderFragmentCode.c_str();
    //// Compile our Fragment shader now
    //fragment = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragment, 1, &fragmentCode, NULL);
    //glCompileShader(fragment);
    //CheckCompileErrors(fragment, "FRAGMENT");

    //// Once we have complied our shaders, attach shaders to program and link them together
    //m_ID = glCreateProgram();
    //glAttachShader(m_ID, vertex);
    //glAttachShader(m_ID, fragment);
    //glLinkProgram(m_ID);
    //CheckLinkingErrors();

    //// With our program made, delete shaders to save on space
    //glDeleteShader(vertex);
    //glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::CompileShaders(std::string& shaderVertexCode, std::string& shaderFragmentCode, std::string& shaderGeometryCode)
{
    unsigned int vertex, fragment;

    // Has to be converted to const char due to how GLAD glShaderSource works (Gives errors if we use string)
    const char* vertexCode = shaderVertexCode.c_str();
    // Compile our Vertex shader now
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // Has to be converted to const char due to how GLAD glShaderSource works (Gives errors if we use string)
    const char* fragmentCode = shaderFragmentCode.c_str();
    // Compile our Fragment shader now
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    if (!shaderGeometryCode.empty())
    {
        // TODO: Compile our geometry shader code here
    }

    // Once we have complied our shaders, attach shaders to program and link them together
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    CheckLinkingErrors();

    // With our program made, delete shaders to save on space
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::ActivateShader()
{
    glUseProgram(m_ID);
}

void Shader::DeactivateShader()
{
    glUseProgram(0);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}


void Shader::SetMatrix4f(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
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