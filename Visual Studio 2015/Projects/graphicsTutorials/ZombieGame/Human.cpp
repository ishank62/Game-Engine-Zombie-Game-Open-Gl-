#include "Human.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

namespace Ishankingen {
Human::Human():frames(0)
{
}


Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos) { 
	//generating random nos.
	static mt19937 randomEngine(time(nullptr));
	static uniform_real_distribution<float> randDir(-1.0f, 1.0f);

	_color.r = 200;
	_color.g = 0;
	_color.b = 200;
	_color.a = 255;

	_speed = speed;
	_position = pos;
	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));//get random direction
	if (_direction.length() == 0)_direction = glm::vec2(1.0f, 0.0f);//make sure direction isnt zero
	_direction = glm::normalize(_direction);//make it unit length
}

void Human::update(const vector<string> &levelData,
	vector<Human*> &humans,
	vector<Zombie*> &zombies) {

	static mt19937 randomEngine(time(nullptr));
	static uniform_real_distribution<float> randRotate(-40.0f, 40.0f);

	_position = _direction*_speed;

	//randomly changing direction of humans every 20 frames
	if (frames == 20) {
		_direction = glm::rotate(_direction, randRotate(randomEngine));
		frames = 0;
	}
	else {
		frames++;
	}

	if(collideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
}
}