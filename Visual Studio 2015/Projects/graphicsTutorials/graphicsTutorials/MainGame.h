#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Ishankingen/Sprite.h>
#include <Ishankingen/GLSLProgram.h>
#include <Ishankingen/GLTexture.h>
#include <Ishankingen/Window.h>
#include <Ishankingen/Camera2D.h>
#include <Ishankingen/SpriteBatch.h>
#include <Ishankingen/InputManager.h>
#include <Ishankingen/Timing.h>
#include "Bullet.h"
#include <vector>

using namespace std;

namespace Ishankingen {
	enum class GameState { PLAY, EXIT };

	class MainGame
	{
	public:
		MainGame();

		void run();

	private:
		void drawGame();
		void processInput();

		void gameLoop();

		void initSystems();

		void initShaders();

		Window _window;
		int _screenWidth;
		int _screenHeight;
		GameState _gameState;

		Camera2D _camera;

		SpriteBatch _spriteBatch;

		InputManager _inputManager;

		FpsLimiter _fpsLimiter;

		GLSLProgram _colorProgram;

		vector<Bullet> _bullets;
		
		float _maxFPS;
		float _fps;
		float _time;
	};

}