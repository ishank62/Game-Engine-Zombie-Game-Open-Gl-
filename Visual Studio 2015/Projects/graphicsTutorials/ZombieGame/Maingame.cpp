#include <iostream>
#include <Ishankingen/InputManager.h>
#include <Ishankingen/Ishankingen.h>
#include <Ishankingen/Timing.h>
#include "Maingame.h"
#include "Zombie.h"
#include <Ishankingen/Errors.h>
#include <SDL/SDL.h>
#include <random>
#include <ctime>
using namespace std;

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.0;

namespace Ishankingen {
Maingame::Maingame(): 
	_screenWidth(1024), 
	_screenHeight(768), 
	_gameState(GameState::PLAY), 
	_fps(0.0f), 
	_player(nullptr)
{}


Maingame::~Maingame(){
	for (int i = 0; i < _levels.size(); i++) {
		delete _levels[i];
	}
}

void Maingame::run() {
	initSystems();

	initLevel();

	gameLoop();
}

void Maingame::initLevel() {
	_levels.push_back(new Level("Levels/level.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(),&_inputManager);

	//coz of  polymorphism since player is a derived class of human class it is gonnna push back it to a human vector
	_humans.push_back(_player);

	mt19937 randomEngine;//no need to be static as done this only 1 time 
	randomEngine.seed(time(nullptr));
	uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);//-1 is not to spawn them at the edge
	uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	//add all random humans
	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++) {
		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED, pos);
	}

	//add the zombies
	const vector<glm::vec2>& zombiePosiitons = _levels[_currentLevel]->getStartZombiePos();
	for (int i = 0; i < zombiePosiitons.size(); i++) {
		_zombies.push_back(new Zombie);
		_zombies.back()->init(ZOMBIE_SPEED, zombiePosiitons[i]);
	}
}

void Maingame::initSystems() {
	init();
	_window.create("Zombie Game", _screenWidth, _screenHeight,0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	initShaders();
	_agentSpriteBatch.init();

	_camera.init(_screenWidth, _screenHeight);
	//Level 1

}
void Maingame::initShaders() {
	_textureProgram.compileShaders("Shaders/colorShading.vert.txt", "Shaders/colorShading.frag.txt");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();
}

void Maingame::gameLoop() {
	FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFps(60.0f);
	while (_gameState == GameState::PLAY) {
		fpsLimiter.begin();

		processInput();

		updateAgents();

		_camera.setPosition(_player->getPosition());
		_camera.update();

		drawGame();

		_fps = fpsLimiter.end();
	}
}

void Maingame::updateAgents() {
	//update the humans
	for (int i = 0; i < _humans.size(); i++) {
		_humans[i]->update(_levels[_currentLevel]->getLevelData(),_humans,_zombies);
	}

	//update the zombies
	for (int i = 0; i < _zombies.size(); i++) {
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
	}

	//update the Humans collisions
	for (int i = 0; i < _humans.size(); i++) {
		for (int j = i + 1; j < _humans.size(); j++) {// check fewer humans
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}

	//update the Zombies collissions
	for (int i = 0; i < _zombies.size(); i++) {
		for (int j = i + 1; j < _zombies.size(); j++) {//check fewer zombies
			_zombies[i]->collideWithAgent(_zombies[j]);
		}
		for (int j = 1; j < _humans.size(); j++) {// check for humans other than player at j=0
			if (_zombies[i]->collideWithAgent(_humans[j])) {
				//add the new zombie to the location of the human
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED,_humans[j]->getPosition());
				//delete the human
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}
		//collide with the player
		if (_zombies[i]->collideWithAgent(_player)){
			fatalError("You Fuckin Lose Goddamnit..!!!");
		}
	}
	//dont forget to update the zombies

}

void Maingame::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			//exit
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN://on key pressed
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP://on key release
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}
}

void Maingame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_textureProgram.use();//Bind buffer

	glActiveTexture(GL_TEXTURE0);//Draws code here

	//make sure the texture uses Texture 0 
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = _camera.getCameraMatrix();//grab the camera matrix
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE,&projectionMatrix[0][0]);

	//draw level
	_levels[_currentLevel]->draw();	

	//begin drawing agents
	_agentSpriteBatch.begin();

	//draw the Humans
	for (int i = 0; i < _humans.size(); i++) {
		_humans[i]->draw(_agentSpriteBatch);
	}

	//draw the Zombies
	for (int i = 0; i < _zombies.size(); i++) {
		_zombies[i]->draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();

	_textureProgram.unuse();//UnBind buffer
	//swap our buffer and draw everything to the screen
	_window.swapBuffer();
}


}