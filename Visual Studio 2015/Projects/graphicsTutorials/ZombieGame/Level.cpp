#include <iostream>
#include "Level.h"
#include <Ishankingen/Errors.h>
#include <Ishankingen/ResourceManager.h>
#include <fstream>
#include <glm/glm.hpp>
using namespace std;

namespace Ishankingen {
Level::Level(const string& fileName) {
	
	ifstream file;
	file.open(fileName);
	if (file.fail()) {
		fatalError("failed to open" + fileName);
	}
	string tmp;
	file >> tmp >> _numHumans;   //throw away the first string in temp
	getline(file, tmp);//throw away the first whole line
	while (getline(file, tmp)) {
		_levelData.push_back(tmp);
	}
	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	//REnder all the tiles
	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[y].size(); x++) {
			char tile = _levelData[y][x];//grab the tile
			
			//get dest rect
			glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//process the tile			 
			switch (tile) {
				case '#':
					_spriteBatch.draw(destRect,uvRect,ResourceManager::getTexture("Textures/Temp/PNG/RedBrick.jpg").id,0.0f,whiteColor);
					break;
				case '!':
					_spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture("Textures/Temp/PNG/greyBrick.jpg").id, 0.0f, whiteColor);
					break;
				case '_':
					break;
				case '@':
					_levelData[y][x]='_';//so we dont collide with a startpos later on
					_startPlayerPos.x = x*TILE_WIDTH;
					_startPlayerPos.y = y*TILE_WIDTH;
					break;
				case 'Z':
					_levelData[y][x] = '_';//so we dont collide with a zombie later on
					_zombieStartPosition.emplace_back(x*TILE_WIDTH, y*TILE_WIDTH);
					break;
				default:
					printf("Unexpected Symbol %c at (%d,%d)", tile, x, y);
					break;
			}
		}

	}
	_spriteBatch.end();
}


Level::~Level()
{
}


void Level::draw() {
	_spriteBatch.renderBatch();		
}
}