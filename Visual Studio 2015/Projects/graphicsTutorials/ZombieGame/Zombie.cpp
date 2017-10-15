#include "Zombie.h"
#include "Human.h"

namespace Ishankingen {
Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}
void Zombie::init(float speed, glm::vec2 pos) {
	_speed = speed;
	_position = pos;
	_color.r = 0;
	_color.g = 160;
	_color.b = 0;
	_color.a = 255;
}

void Zombie::update(const vector<string> &levelData,
	vector<Human*> &humans,
	vector<Zombie*> &zombies) {

	Human* closestHuman = getNearestHuman(humans);
	if (closestHuman != nullptr) {
		glm::vec2 direction = glm::normalize(closestHuman->getPosition() - _position);
		_position += direction* _speed;
	}

	collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(vector<Human*>& humans) {
	Human* nearestHuman = nullptr;
	float smallestDistance = 9999999.0f;

	for (int i = 0; i < humans.size(); i++) {
		glm::vec2 distVec = humans[i]->getPosition() - _position;
		float distance = glm::length(distVec);

		if (distance < smallestDistance) {
			smallestDistance = distance;
			nearestHuman = humans[i];
		}
		return nearestHuman;
	}
}
}