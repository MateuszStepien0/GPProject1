#include <Game.h>
#include <Cube.h>

// Helper to convert Number to String for HUD
template <typename T>

string toString(T number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}

GLuint	vsid,		// Vertex Shader ID
		fsid,		// Fragment Shader ID
		progID,		// Program ID
		vao = 0,	// Vertex Array ID
		vbo,		// Vertex Buffer ID
		vib,		// Vertex Index Buffer
		to[1];		// Texture ID
GLint	positionID,	// Position ID
		colorID,	// Color ID
		textureID,	// Texture ID
		uvID,		// UV ID
		mvpID,		// Model View Projection ID
		x_offsetID, // X offset ID
		y_offsetID,	// Y offset ID
		z_offsetID;	// Z offset ID

GLenum	error;		// OpenGL Error Code


const string filename = ".//Assets//Textures//Cube.tga";
const string filename2 = ".//Assets//Textures//PlayerCube.tga";
const string filename3 = ".//Assets//Textures//Spike.tga";
const string filename4 = ".//Assets//Textures//ObjectCube.tga";

int width;						// Width of texture
int height;						// Height of texture
int comp_count;					// Component of texture

unsigned char* img_data;		// image data
unsigned char* img_data2;		// image data
unsigned char* img_data3;		// image data
unsigned char* img_data4;		// image data

mat4 mvp, projection;			// Model View Projection

Game::Game() : 
	m_window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing")
{
}

Game::Game(sf::ContextSettings settings) : 
	m_window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing", 
	sf::Style::Default, 
	settings)
{
	for (int i = 0; i < GAME_OBJECTS - 20; i++)
	{
		m_gameObject[i] = new GameObject();
		m_gameObject[i]->setPosition(vec3(0.0f, 0.0f, i * -2.0f));
	}

	int index = 20;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 4.0f, -14.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 4.0f, -16.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 8.0f, -24.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 8.0f, -26.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 10.0f, -34.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 10.0f, -36.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 8.0f, -44.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 8.0f, -46.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 8.0f, -48.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 4.0f, -100.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 4.0f, -102.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 8.0f, -110.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 8.0f, -112.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 12.0f, -120.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 12.0f, -122.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 14.0f, -130.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 14.0f, -132.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 12.0f, -140.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 12.0f, -142.0f));
	index--;

	m_gameObject[GAME_OBJECTS - index] = new GameObject();
	m_gameObject[GAME_OBJECTS - index]->setPosition(vec3(0.0f, 12.0f, -152.0f));
	index--;

	m_playerObject = new PlayerObject();
	m_playerObject->setPosition(vec3(0.0f, 2.0f, 0.0f));

	m_endGoalObject = new EndGoal();
	m_endGoalObject->setPosition(vec3(0.0f, 2.5f, -250.0f));

	int offset = 0;
	for (int i = 0; i < SPIKE_OBJECTS; i++)
	{
		if (i % 3 == 0)
		{
			offset += -12.0f;
		}

		m_spikeObject[i] = new SpikeObject();
		m_spikeObject[i]->setPosition(vec3(0.0f, 2.0f, i * -2.0f + offset - 16.0f));
	}
}

Game::~Game()
{
}


void Game::run()
{
	initialize();

	// Game clock
	sf::Clock clock;

	const float FPS = 60.0f;

	// 1 / 60th of a second.
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	// Time since the last time the game updated.
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	Event event;

	while (m_isRunning)
	{
		while (m_window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				m_isRunning = false;
			}
		}

		//Get the time since last update and restart the clock.
		timeSinceLastUpdate += clock.restart();
		//Update every 60th of a second.
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate);
			timeSinceLastUpdate = sf::seconds(0.0f);
		}
		render();
	}

	unload();
}

void Game::initialize()
{
	m_isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	if (!(!glewInit())) { DEBUG_MSG("glewInit() failed"); }

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	// Vertex Array Buffer
	glGenBuffers(1, &vbo);		// Generate Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Store all the vertices and uvs for both cube and spike.
	glBufferData(GL_ARRAY_BUFFER, ((3 * CUBE_VERTICES) + (2 * CUBE_UVS) + (3 * SPIKE_VERTICES) + (2 * SPIKE_UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); // Generate Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (3 * CUBE_INDICES + 3 * SPIKE_INDICES) * sizeof(GLuint), indices, GL_STATIC_DRAW);

	const char* vs_src =
		"#version 400\n\r"
		""
		"in vec3 sv_position;"
		"in vec2 sv_uv;"
		""
		"out vec2 uv;"
		""
		"uniform mat4 sv_mvp;"
		""
		"void main() {"
		"	uv = sv_uv;"
		"	gl_Position = sv_mvp * vec4(sv_position, 1);"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
	glCompileShader(vsid);

	// Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	const char* fs_src =
		"#version 400\n\r"
		""
		"uniform sampler2D f_texture;"
		""
		"in vec2 uv;"
		""
		"out vec4 fColor;"
		""
		"void main() {"
		"	fColor = texture2D(f_texture, uv.st);"
		""
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);

	// Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();
	glAttachShader(progID, vsid);
	glAttachShader(progID, fsid);
	glLinkProgram(progID);

	// Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Set image data
	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);
	img_data2 = stbi_load(filename2.c_str(), &width, &height, &comp_count, 4);
	img_data3 = stbi_load(filename3.c_str(), &width, &height, &comp_count, 4);
	img_data4 = stbi_load(filename4.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to[0]);
	glBindTexture(GL_TEXTURE_2D, to[0]);

	// Wrap around
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Bind to OpenGL
	glTexImage2D(
		GL_TEXTURE_2D,	// 2D Texture Image
		0,				// Mipmapping Level 
		GL_RGBA,		// GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,			// Width
		height,			// Height
		0,				// Border
		GL_RGBA,		// Bitmap
		GL_UNSIGNED_BYTE,
		img_data
		);

	// Projection Matrix 
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		5.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
		);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// Load Font
	if (!m_font.loadFromFile(".//Assets//Fonts//BBrick.ttf"))
	{
		cout << "font not loaded" << endl;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	m_playerObject->update(t_deltaTime);
	m_camera.update(m_playerObject->getPosition());
	m_endGoalObject->update();

	bool onGround = false;

	for (int i = 0; i < GAME_OBJECTS; i++)
	{
		// Has the player collided with GameObject
		if (m_gameObject[i]->m_collisionBox.getGlobalBounds().intersects(m_playerObject->m_collisionBox.getGlobalBounds()))
		{
			// Was the player above the GameObject
			if (m_playerObject->getPreviousPos().y > m_gameObject[i]->getPosition().y + 1.5f)
			{
				m_playerObject->setPosition(vec3(m_playerObject->getPosition().x, m_gameObject[i]->getPosition().y + 2.0f, m_playerObject->getPosition().z));
				m_playerObject->onGround();
			}
			// Was the player below the GameObject
			else if (m_playerObject->getPreviousPos().y < m_gameObject[i]->getPosition().y - 1.5f)
			{
				m_playerObject->setPosition(vec3(m_playerObject->getPosition().x, m_gameObject[i]->getPosition().y - 2.0f, m_playerObject->getPosition().z));
			}
			// The player must be to the side if all of the above are false
			else
			{
				m_playerObject->setPosition(vec3(m_playerObject->getPosition().x, m_playerObject->getPosition().y, m_gameObject[i]->getPosition().z + 2.0f));
			}
		}
	}

	//Has the player collided with the goal
	if (m_endGoalObject->m_collisionBox.getGlobalBounds().intersects(m_playerObject->m_collisionBox.getGlobalBounds()))
	{
		resetGame();
	}

	for (int i = 0; i < SPIKE_OBJECTS; i++)
	{
		// Has the player collided with a spike
		if (m_spikeObject[i]->m_collisionBox.getGlobalBounds().intersects(m_playerObject->m_collisionBox.getGlobalBounds()))
		{
			resetGame();
			break;
		}
	}
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save current OpenGL render states
	m_window.pushGLStates();

	// Restore OpenGL render states
	m_window.popGLStates();

	// Rebind Buffers and then set SubData
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Use Progam on GPU
	glUseProgram(progID);

	// Find variables within the shader
	positionID = glGetAttribLocation(progID, "sv_position");
	if (positionID < 0) { DEBUG_MSG("positionID not found"); }

	uvID = glGetAttribLocation(progID, "sv_uv");
	if (uvID < 0) { DEBUG_MSG("uvID not found"); }

	textureID = glGetUniformLocation(progID, "f_texture");
	if (textureID < 0) { DEBUG_MSG("textureID not found"); }

	mvpID = glGetUniformLocation(progID, "sv_mvp");
	if (mvpID < 0) { DEBUG_MSG("mvpID not found"); }
	
	// Spikes
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * CUBE_VERTICES) + (2 * CUBE_UVS)) * sizeof(GLfloat), 3 * SPIKE_VERTICES * sizeof(GLfloat), spikeVertices);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * CUBE_VERTICES) + (2 * CUBE_UVS) + (3 * SPIKE_VERTICES)) * sizeof(GLfloat), 2 * SPIKE_UVS * sizeof(GLfloat), spikeUvs);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(positionID);
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * CUBE_VERTICES) + (2 * CUBE_UVS)) * sizeof(GLfloat)));

	glEnableVertexAttribArray(uvID);
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * CUBE_VERTICES) + (2 * CUBE_UVS) + (3 * SPIKE_VERTICES)) * sizeof(GLfloat)));

	bindSpikeTex();

	//Draw SpikeObjects
	for (int i = 0; i < SPIKE_OBJECTS; i++)
	{
		mvp = projection * m_camera.getWorldToViewMatrix() * m_spikeObject[i]->getModelToWorldMatrix();
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
		glDrawElements(GL_TRIANGLES, 3 * SPIKE_INDICES, GL_UNSIGNED_INT, NULL);
	}

	// Cubes
	glBufferSubData(GL_ARRAY_BUFFER, 0 * CUBE_VERTICES * sizeof(GLfloat), 3 * CUBE_VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, (3 * CUBE_VERTICES) * sizeof(GLfloat), 2 * CUBE_UVS * sizeof(GLfloat), uvs);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(positionID);
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(uvID);
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * CUBE_VERTICES)) * sizeof(GLfloat)));

	bindObjectTex();

	// Draw GameObjects 
	for (int i = 0; i < GAME_OBJECTS; i++)
	{
		mvp = projection * m_camera.getWorldToViewMatrix() * m_gameObject[i]->getModelToWorldMatrix();
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
		glDrawElements(GL_TRIANGLES, 3 * CUBE_INDICES, GL_UNSIGNED_INT, NULL);
	}

	mvp = projection * m_camera.getWorldToViewMatrix() * m_endGoalObject->getModelToWorldMatrix();
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
	glDrawElements(GL_TRIANGLES, 3 * CUBE_INDICES, GL_UNSIGNED_INT, NULL);

	bindPlayerTex();

	//Draw playerObject cubes.
	mvp = projection * m_camera.getWorldToViewMatrix() * m_playerObject->getModelToWorldMatrix();
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
	glDrawElements(GL_TRIANGLES, 3 * CUBE_INDICES, GL_UNSIGNED_INT, NULL);

	m_window.display();
}

void Game::unload()
{
	glDetachShader(progID, vsid);	// Shader could be used with more than one progID
	glDetachShader(progID, fsid);	// ..
	glDeleteShader(vsid);			// Delete Vertex Shader
	glDeleteShader(fsid);			// Delete Fragment Shader
	glDeleteProgram(progID);		// Delete Shader
	glDeleteBuffers(1, &vbo);		// Delete Vertex Buffer
	glDeleteBuffers(1, &vib);		// Delete Vertex Index Buffer
	stbi_image_free(img_data);		// Free image stbi_image_free(..)
}

void Game::resetGame()
{
	m_playerObject->setPosition(vec3(0.0f, 2.0f, 0.0f));
	m_playerObject->changeVelocity(1.0f);
}

void Game::bindSpikeTex()
{
	// Bind to OpenGL
	glTexImage2D(
		GL_TEXTURE_2D,	//2D Texture Image
		0,				//Mipmapping Level 
		GL_RGBA,		//GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,			//Width
		height,			//Height
		0,				//Border
		GL_RGBA,		//Bitmap
		GL_UNSIGNED_BYTE,
		img_data3);
}

void Game::bindPlayerTex()
{
	// Bind to OpenGL
	glTexImage2D(
		GL_TEXTURE_2D,	//2D Texture Image
		0,				//Mipmapping Level 
		GL_RGBA,		//GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,			//Width
		height,			//Height
		0,				//Border
		GL_RGBA,		//Bitmap
		GL_UNSIGNED_BYTE,
		img_data2);
}

void Game::bindObjectTex()
{
	// Bind to OpenGL
	glTexImage2D(
		GL_TEXTURE_2D,	//2D Texture Image
		0,				//Mipmapping Level 
		GL_RGBA,		//GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,			//Width
		height,			//Height
		0,				//Border
		GL_RGBA,		//Bitmap
		GL_UNSIGNED_BYTE,
		img_data4);
}

void Game::bindGoalTex()
{
	// Bind to OpenGL
	glTexImage2D(
		GL_TEXTURE_2D,	//2D Texture Image
		0,				//Mipmapping Level 
		GL_RGBA,		//GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,			//Width
		height,			//Height
		0,				//Border
		GL_RGBA,		//Bitmap
		GL_UNSIGNED_BYTE,
		img_data);
}

