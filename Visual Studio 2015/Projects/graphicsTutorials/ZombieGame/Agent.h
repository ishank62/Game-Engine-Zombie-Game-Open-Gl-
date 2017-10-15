#pragma once
#include <glm/glm.hpp>
#include <Ishankingen/SpriteBatch.h>


namespace Ishankingen {

class Zombie;//we now dont have to include header files for these for preventing circular includes  
class Human;

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;
class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update(const vector<string> &levelData,
						vector<Human*> &humans,
						vector<Zombie*> &zombies) = 0;  /*0 denotes that the function is a pure virtual function 
	ie. u cannot have agent class but only derived class implement this function
	and every class that derives from Agent has to have this update function*/

	bool collideWithLevel(const vector<string> &levelData);

	bool collideWithAgent(Agent* agent);

	void draw(SpriteBatch& _spriteBatch);

	glm::vec2 getPosition() { return _position; }
protected:
	void checkTilePostion(const vector<string> &levelData,
						  vector<glm::vec2> _collideTilePosiitons,
						  float x, 
						  float y);
	void collideWithTile(glm::vec2 tilePos);
	glm::vec2 _position;
	Color _color;
	float _speed;
};
}
