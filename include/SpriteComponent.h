#pragma once

#include <glad/glad.h>
#include <../glm/glm.hpp>

#include "Texture2D.h"
#include "BaseComponent.h"
#include "Renderer.h"

class SpriteComponent : public IBaseComponent
{
public:
	Texture2D m_sprite;

	SpriteComponent();
	SpriteComponent(Texture2D);
	~SpriteComponent();

	void Draw(Renderer& renderer, glm::vec2, glm::vec2, float, glm::vec3) override;
private:
	
};