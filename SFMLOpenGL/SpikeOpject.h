#pragma once

#include <stdio.h>
#include <string.h>
#include <Spike.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>

using namespace glm;

class SpikeObject
{
private:

	// Position of the SpikeObject
	vec3 m_position;

	// Rotation of the SpikeObject
	vec3 m_rotation;

public:
	SpikeObject();
	~SpikeObject();

	sf::RectangleShape m_collisionBox;

	vec3 getPosition();
	void setPosition(vec3 position);

	mat4 getModelToWorldMatrix();

};