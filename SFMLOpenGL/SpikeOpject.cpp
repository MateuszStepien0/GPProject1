#include "SpikeOpject.h"

SpikeObject::SpikeObject()
	: m_rotation(1.0f, 0.0f, 0.0f)
{
	m_position = vec3(0.0f, 0.0f, 0.0f);

	m_collisionBox.setSize(sf::Vector2f(1.5f, 1.5f));
	m_collisionBox.setOrigin(0.75f, 0.75f);
	m_collisionBox.setPosition(m_position.z, m_position.y);
}

SpikeObject::~SpikeObject()
{
}

vec3 SpikeObject::getPosition()
{
	return m_position;
}

void SpikeObject::setPosition(vec3 position)
{
	m_position = position;
	m_collisionBox.setPosition(m_position.z, m_position.y);
}

mat4 SpikeObject::getModelToWorldMatrix()
{
	return mat4(translate(glm::mat4(1.f), m_position) * rotate(glm::mat4(1.f), 0.0f, m_rotation));
}
