#pragma once
#include <glm/glm.hpp>
#include <Ishankingen/SpriteBatch.h>

using namespace std;

namespace Ishankingen {
class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();

	void draw(SpriteBatch& spriteBatch);
	
	// returns true when bullet is out of life
	bool update();
private:
	int _lifeTime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
};
}