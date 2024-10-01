#include "Sprite.h"

Sprite::Sprite() : m_sprite()
{
}

Sprite::Sprite(Texture2D sprite) : m_sprite(sprite)
{
}

Sprite::~Sprite()
{
}

void Sprite::Draw(Renderer& renderer, glm::vec2 pos, glm::vec2 size, float rotation, glm::vec3 color)
{
	renderer.DrawSprite(m_sprite, pos, size, rotation, color);
}