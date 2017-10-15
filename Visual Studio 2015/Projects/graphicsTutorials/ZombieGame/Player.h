#pragma once
#include <Ishankingen/InputManager.h>
#include "Human.h"

namespace Ishankingen {
class Player :public Human
{
public:
	Player();
	virtual ~Player();	
	void init(float speed, glm::vec2 pos, InputManager* inputManager);

	void update(const vector<string> &levelData,
		vector<Human*> &humans,
		vector<Zombie*> &zombies);
private:
	InputManager* _inputManager;
};

}