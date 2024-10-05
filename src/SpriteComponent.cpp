#include "SpriteComponent.h"

SpriteComponent::SpriteComponent() : m_sprite()
{
}

SpriteComponent::SpriteComponent(Texture2D sprite) : m_sprite(sprite)
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw(Renderer& renderer, glm::vec2 pos, glm::vec2 size, float rotation, glm::vec3 color)
{
	renderer.DrawSprite(m_sprite, pos, size, rotation, color);
}