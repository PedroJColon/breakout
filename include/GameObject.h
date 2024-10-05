#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm.hpp>
#include <vector>
#include <memory>

#include "BaseComponent.h"
#include "Renderer.h"

enum ID
{
	PLAYER,
	BALL,
	SOLIDBRICK,
	BRICK,
};

class GameObject
{
public:
	glm::vec2 m_pos, m_size, m_velocity;
	glm::vec3 m_color;
	float m_rotation;
	float m_radius;
	float m_stuck;
	bool m_isSolid;
	bool m_destroyed;

	ID m_ID;

	std::vector<std::shared_ptr<IBaseComponent>> m_component;

	GameObject();
	GameObject(glm::vec2, glm::vec2, ID, glm::vec3 = glm::vec3(1.0f), glm::vec2 = glm::vec2(0.0f, 0.0f));
	~GameObject();

	glm::vec2 Move(float, unsigned int);
	void Reset(glm::vec2, glm::vec2);
	void AddComponent(std::shared_ptr<IBaseComponent>);

private:

};

#endif // !GAMEOBJECT_H