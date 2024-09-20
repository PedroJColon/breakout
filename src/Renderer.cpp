#include "Renderer.h"

Renderer::Renderer(Shader& shader)
{
	m_shader = shader;
	InitRenderer();
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &m_VAO);
}

void Renderer::DrawSprite(Texture2D& texture, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color)
{
	m_shader.ActivateShader();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5 * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	m_shader.SetMatrix4f("model", model);
	m_shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::InitRenderer()
{
	float vertices[] =
	{
		// pos // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
