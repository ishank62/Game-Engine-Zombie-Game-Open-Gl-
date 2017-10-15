#include "Agent.h"
#include <Ishankingen/ResourceManager.h>
#include "Level.h"
#include <algorithm>

namespace Ishankingen {
Agent::Agent()
{
}


Agent::~Agent()
{
}
bool Agent::collideWithLevel(const vector<string> &levelData) {
	vector<glm::vec2> collideTilePosiitons;
	//check the four corners
	//first corner
	checkTilePostion(levelData, collideTilePosiitons, _position.x, _position.y);

	//second corner
	checkTilePostion(levelData, collideTilePosiitons, _position.x + AGENT_WIDTH, _position.y);

	//third corner
	checkTilePostion(levelData, collideTilePosiitons, _position.x, _position.y  + AGENT_WIDTH);

	//fourth corner
	checkTilePostion(levelData, collideTilePosiitons, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

	if (collideTilePosiitons.size() == 0) {
		return false;
	}

	//do the collision
	for (int i = 0; i < collideTilePosiitons.size(); i++) {
		collideWithTile(collideTilePosiitons[i]);
	}
	return true;
}

bool Agent::collideWithAgent(Agent* agent) {
	const float MIN_DISTANCE = AGENT_RADIUS * 2.0f;

	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collissionDepth = MIN_DISTANCE - distance;
	if (collissionDepth > 0) {//then we have a collision in humans
		glm::vec2 collissiondepthVec = glm::normalize(distVec) * collissionDepth;
		_position += collissiondepthVec / 2.0f;
		agent->_position -= collissiondepthVec / 2.0f;//push out both by half distance
		return true;
	}
	return false;
	
}

void Agent::draw(SpriteBatch& _spriteBatch) {
	static int textureId = ResourceManager::getTexture("Textures/Temp/PNG/circle.png").id;

	const glm::vec4 uvRect(0.0f,0.0f,1.0f,1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;


	_spriteBatch.draw(destRect, uvRect, textureId, 0.0f, _color);

}
void Agent::checkTilePostion(const vector<string> &levelData,vector<glm::vec2> _collideTilePosiitons,float x,float y) {
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));//multiply and divide to get precise float corner position 

	//if we r outsode the world just return
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size()) {
		return;
	}
	if (levelData[cornerPos.y][cornerPos.x] != '_') {
		_collideTilePosiitons.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

//Axis aligned bounding box collision
void Agent::collideWithTile(glm::vec2 tilePos) {
	
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	//if this happens then we have a collision
	if (xDepth > 0 || yDepth > 0) {
		if (max(xDepth,0.0f) <max(yDepth,0.0f) ) {
			if (distVec.x < 0) {
				_position.x += xDepth;
			}
			else {
				_position.x -= xDepth;
			}
		}
		else {
			if (distVec.y < 0) {
				_position.y -= yDepth;
			}
			else {
				_position.y += yDepth;
			}
			
		}
	}
}
}