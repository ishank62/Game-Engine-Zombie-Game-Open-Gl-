#pragma once

#include "Agent.h"

namespace Ishankingen {
class Human :public Agent
{
public:
	Human();
	virtual ~Human();

	void init(float speed, glm::vec2 pos);//not usign inputmanager for humans coz they gonna walk sround themselves using a simple ai

	virtual void update(const vector<string> &levelData,
		vector<Human*> &humans,
		vector<Zombie*> &zombies);
private:
	glm::vec2 _direction;
	int frames;
};

}