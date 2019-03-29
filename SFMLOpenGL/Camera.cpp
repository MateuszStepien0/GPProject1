#include "Camera.h"

Camera::Camera()
	: m_viewDirection(0.0f, 0.0f, 0.0f)
	, m_position(10.0f, 10.0f, 0.0f)
	, UP(0.0f, 1.0f, 0.0f)
	, m_offSet(20.0f, 0.0, 0.0f)
	, m_rotate(false)
	, m_rotated(m_rotate)
{
}

Camera::~Camera()
{
}

void Camera::update(glm::vec3 t_playerPos)
{
	m_rotate = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		m_rotate = true;
	}

	if (!m_rotated && m_rotate)
	{
		if (glm::vec3(20.0f, 0.0, 0.0f) == m_offSet)
		{
			m_offSet = glm::vec3(5.0f, 5.0f, 10.0f);
		}
		else
		{
			m_offSet = glm::vec3(20.0f, 0.0, 0.0f);
		}
	}

	m_position = t_playerPos + m_offSet;
	m_viewDirection = t_playerPos;

	m_rotated = m_rotate;
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(m_position, m_viewDirection, UP);
}

