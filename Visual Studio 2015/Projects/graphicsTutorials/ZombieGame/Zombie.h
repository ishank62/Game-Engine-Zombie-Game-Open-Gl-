#pragma once
#include "Agent.h"

namespace Ishankingen {
class Zombie :public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 pos);

	virtual void update(const vector<string> &levelData,
		vector<Human*> &humans,
		vector<Zombie*> &zombies);
private:
	Human* getNearestHuman(vector<Human*>& humans);
};
}

