#pragma once
#include <Ishankingen/GLSLProgram.h>
#include <Ishankingen/Window.h>
#include <Ishankingen/Camera2D.h>
#include <Ishankingen/InputManager.h>
#include <Ishankingen/SpriteBatch.h>
#include "Player.h"
#include "Level.h"

class Zombie;
enum class GameState {
	PLAY, EXIT
};

namespace Ishankingen {
class Maingame
{
public:
	Maingame();
	~Maingame();

	void run();
private:
	void initSystems();

	void initLevel();

	void initShaders();

	void gameLoop();

	void updateAgents();//update all agents

	void drawGame();

	void processInput();

	Window _window;

	InputManager _inputManager;

	Camera2D _camera;
	SpriteBatch _agentSpriteBatch;//draw all agents

	GLSLProgram _textureProgram;

	vector<Level*> _levels;//vector of all Levels

	int _screenWidth, _screenHeight;
	
	GameState _gameState;
	
	float _fps;

	int _currentLevel;

	Player* _player;

	vector<Human*> _humans;//vector of all humans that r gonna be chased by the zombies
	vector<Zombie*> _zombies;//vector of all zombies
	};
}
