#include "GameObject.h"
#include "GameObject.h"

GameObject::GameObject() : m_pos(0), m_size(1), m_velocity(0.0f), m_color(1.0f), m_rotation(0.0f), 
m_isSolid(false), m_destroyed(false)
{
	m_radius = 0.0f;
	m_stuck = false;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, ID objectID, glm::vec3 color, glm::vec2 velocity)  : m_pos(pos), m_size(size), m_color(color),
m_velocity(velocity), m_rotation(0.0f), m_isSolid(false), m_destroyed(false), m_ID(objectID)
{
	m_radius = 0.0f;
	m_stuck = false;
}

GameObject::~GameObject()
{
}

glm::vec2 GameObject::Move(float deltaTime, unsigned int windowWidth)
{
	if (!m_stuck)
	{
		m_pos += m_velocity * deltaTime;

		if (m_pos.x <= 0.0f)
		{
			m_velocity.x = -m_velocity.x;
			m_pos.x = 0.0f;
		}
		else if (m_pos.x + m_size.x >= windowWidth)
		{
			m_velocity.x = -m_velocity.x;
			m_pos.x = windowWidth - m_size.x;
		}
		if (m_pos.y <= 0.0f)
		{
			m_velocity.y = -m_velocity.y;
			m_pos.y = 0.0f;
		}
	}

	return m_pos;
}

void GameObject::Reset(glm::vec2 pos, glm::vec2 velocity)
{
	m_pos = pos;
	m_velocity = velocity;
	m_stuck = true;
}

void GameObject::AddComponent(std::shared_ptr<IBaseComponent> comp)
{
	m_component.push_back(comp);
}
