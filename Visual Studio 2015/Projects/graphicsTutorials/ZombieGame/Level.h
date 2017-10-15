#pragma once
#pragma once
#include <Ishankingen/SpriteBatch.h>
#include <string>
#include <vector>
using namespace std;
const int TILE_WIDTH = 64;

namespace Ishankingen {
class Level
{
public:
	Level(const string& fileName);
	~Level();

	void draw();
	//getters
	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }//actually a string so whne not looking at a string its in y direction
	int getNumHumans() const { return _numHumans; }
	const vector<string>& getLevelData() const { return _levelData; }
	glm::vec2 getStartPlayerPos() const {
		return _startPlayerPos;
	}
	const vector<glm::vec2> getStartZombiePos() const {
		return _zombieStartPosition;
	}
private:
	vector<string> _levelData;
	int _numHumans;
	SpriteBatch _spriteBatch;
	glm::vec2 _startPlayerPos;//integer vector
	vector<glm::vec2> _zombieStartPosition;
};
}
