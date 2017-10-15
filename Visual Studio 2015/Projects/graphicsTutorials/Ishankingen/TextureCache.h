#pragma once
#include <map>
#include "GLTexture.h"
using namespace std;


	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(string texuturePath);

	private:
		map < string, GLTexture> _textureMap;
	};
