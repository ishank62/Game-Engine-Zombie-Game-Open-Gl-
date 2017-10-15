#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>
using namespace std;


	void fatalError(string errorString) {
		cout << errorString;
		cout << "Enter any key to exit";
		int tmp;
		cin >> tmp;
		SDL_Quit();
		exit(1);
	}
