#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <stdio.h>
#include <string.h>
#include <Cube.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>

using namespace glm;

class GameObject
{
private:

	vec3 m_position;

	vec3 m_rotation;
public:
	GameObject();
	~GameObject();

	sf::RectangleShape m_collisionBox;

	vec3 getPosition();
	void setPosition(vec3 position);

	mat4 getModelToWorldMatrix();
};

#endif // !GAME_OBJECT_H

