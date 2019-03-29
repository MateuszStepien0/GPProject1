#include "EndGoal.h"

EndGoal::EndGoal()
	: m_rotation(0.0f)
{
	m_position = vec3(0.0f, 0.0f, 0.0f);

	m_collisionBox.setSize(sf::Vector2f(2.0f, 2.0f));
	m_collisionBox.setOrigin(1.0f, 1.0f);
	m_collisionBox.setPosition(m_position.z, m_position.y);
}

void EndGoal::update()
{
	m_rotation += 0.01f;

	if (m_rotation > 360.0f)
	{
		m_rotation = 0.0f;
	}
}

vec3 EndGoal::getPosition()
{
	return m_position;
}

void EndGoal::setPosition(vec3 position)
{
	m_position = position;
	m_collisionBox.setPosition(m_position.z, m_position.y);
}

mat4 EndGoal::getModelToWorldMatrix()
{
	return mat4(translate(glm::mat4(1.f), m_position) * rotate(glm::mat4(1.f), m_rotation, vec3(1.0f, 0.0f, 0.0f)));
}
