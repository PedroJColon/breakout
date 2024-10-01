#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm.hpp>

#include "Texture2D.h"
#include "Renderer.h"

class GameObject
{
public:
	glm::vec2 m_pos, m_size, m_velocity;
	glm::vec3 m_color;
	float m_rotation;
	bool m_isSolid;
	bool m_destroyed;

	GameObject();
	GameObject(glm::vec2, glm::vec2, glm::vec3 = glm::vec3(1.0f), glm::vec2 = glm::vec2(0.0f, 0.0f));
	~GameObject();

private:

};

#endif // !GAMEOBJECT_H