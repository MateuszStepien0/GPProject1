#pragma once

#include <stdio.h>
#include <string.h>
#include <Cube.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>

using namespace glm;

class PlayerObject
{
private:

	// Previous position of the PlayerObject
	vec3 m_previousPos;

	// Position of the PlayerObject
	vec3 m_position;

	// Rotation of the PlayerObject
	vec3 m_rotation;

	// Velocity vector of PlayerObject
	vec3 m_velocity;

	// Acceleration vector of PlayerObject
	vec3 m_acceleration;

	// Jump velocity vector of PlayerObject.
	vec3 m_jumpVelocity;

public:
	PlayerObject();
	~PlayerObject();

	sf::RectangleShape m_collisionBox;

	void update(sf::Time t_deltaTime);

	vec3 getPosition();
	void setPosition(vec3 position);
	vec3 getPreviousPos();

	mat4 getModelToWorldMatrix();

	void changeVelocity(float t_multiplier);

	void onGround();
};

