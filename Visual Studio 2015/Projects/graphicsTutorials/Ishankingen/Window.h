#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
using namespace std;


	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(string WindowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();
		int getScreenWidth() { _screenWidth; }
		int getScreenHeigth() { _screenHeight; }

	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;
	};
