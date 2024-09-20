#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "Shader.h"
#include "Texture2D.h"

class Renderer
{
private:
	Shader m_shader;
	unsigned int m_VAO;

public:
	Renderer(Shader&);
	~Renderer();

	void DrawSprite(Texture2D&, glm::vec2, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));

private:
	void InitRenderer();
};


#endif // !RENDERER_H