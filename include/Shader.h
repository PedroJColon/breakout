#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    /* data */
public:
    Shader(/* args */);
    ~Shader();

    // UTILITY FUNCTIONS (MATH-RELATED)
    void SetInt();
    void SetFloat();
    void SetVector2f();
    void SetVector3f();
    void SetVector4f();
    void SetMatrix4f();
private:
    // Check compliation error
    //
};

#endif // SHADER_H