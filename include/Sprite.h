#pragma once

#include <glad/glad.h>
#include <../glm/glm.hpp>

#include "Texture2D.h"
#include "Renderer.h"

class Sprite
{
public:
	Texture2D m_sprite;

	Sprite();
	Sprite(Texture2D);
	~Sprite();

	void Draw(Renderer& renderer, glm::vec2, glm::vec2, float, glm::vec3);
private:
	
};