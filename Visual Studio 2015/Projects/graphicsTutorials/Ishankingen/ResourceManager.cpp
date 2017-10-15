#include "ResourceManager.h"



	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(string texuturePath) {
		return _textureCache.getTexture(texuturePath);
	}