#ifndef GAME_H
#define GAME_H

#include <string>
#include <sstream>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <Debug.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GameObject.h>
#include <PlayerObject.h>
#include <SpikeOpject.h>
#include <Camera.h>
#include <EndGoal.h>

using namespace std;
using namespace sf;
using namespace glm;

class Game
{
public:
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();

private:
	const int GAME_OBJECTS{ 150 };
	const int SPIKE_OBJECTS{ 21 };

	GameObject * m_gameObject[150];
	PlayerObject * m_playerObject;
	SpikeObject * m_spikeObject[21];
	EndGoal * m_endGoalObject;

	RenderWindow m_window;
	Camera m_camera;

	Font m_font;

	bool m_isRunning = false;

	void initialize();
	void update(sf::Time t_deltaTime);
	void render();
	void unload();

	void resetGame();

	void bindSpikeTex();
	void bindPlayerTex();
	void bindObjectTex();
	void bindGoalTex();

};

#endif  // ! GAME_H