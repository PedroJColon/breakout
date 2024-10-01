#include <GameObject.h>

GameObject::GameObject() : m_pos(0), m_size(1), m_velocity(0.0f), m_color(1.0f), m_rotation(0.0f), 
m_isSolid(false), m_destroyed(false)
{
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) : m_pos(pos), m_size(size), m_color(color),
m_velocity(velocity), m_rotation(0.0f), m_isSolid(false), m_destroyed(false)
{
}

GameObject::~GameObject()
{
}
