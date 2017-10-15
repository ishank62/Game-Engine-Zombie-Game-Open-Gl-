#pragma once
#include "TextureCache.h"


	class ResourceManager
	{
	public:
		static GLTexture getTexture(string texuturePath);
	private:
		static TextureCache _textureCache;
	};

