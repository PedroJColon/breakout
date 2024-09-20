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
public:
    // MEMBER VARIABLES
    unsigned int m_ID; // Shader Program ID - Important for us to free shader resource when needed

    // CONSTRUCTORS
    Shader(); // Empty default constructor made to make linker happy - Will not be used often if at all
    Shader(std::string&, std::string&); // This constructor will be used to create and compile shaders into a shader program
    // DESTRUCTORS
    ~Shader();

    void CompileShaders(std::string&, std::string&, std::string&);
    void ActivateShader(); // Activates Shader with its ID value
    void DeactivateShader(); // Deactivates Shader into a zero value
    // UTILITY FUNCTIONS (MATH-RELATED)
    void SetInt(const std::string&, int) const;
    // void SetFloat(const std::string&, float) const;
    // void SetVector2f(const std::string&, glm::vec2) const;
    // void SetVector3f(const std::string&, glm::vec3) const;
    // void SetVector4f(const std::string&, glm::vec4) const;
    void SetMatrix4f(const std::string&, glm::mat4) const;

private:
    // UTILITY FUNCTIONS
    void CheckCompileErrors(unsigned int, std::string); // Check for any compliation errors with shader code
    void CheckLinkingErrors(); // Check for any linkage error with shader program
};

#endif // SHADER_H