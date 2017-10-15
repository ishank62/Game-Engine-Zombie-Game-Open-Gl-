#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>


	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}


	GLTexture TextureCache::getTexture(string texuturePath) {
		auto mit = _textureMap.find(texuturePath);
		if (mit == _textureMap.end()) {//if not found in map
			GLTexture newTexture = ImageLoader::loadPNG(texuturePath);

			_textureMap.insert(make_pair(texuturePath, newTexture));//insert it into map
			return newTexture;
		}
		return mit->second;
	}
