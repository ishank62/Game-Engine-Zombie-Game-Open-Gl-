#pragma once
#include <glm/glm.hpp>
#include <unordered_map>// like a normal map but inside its stored like a hash table thus faster
using namespace std;


	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		bool isKeyPressed(unsigned int keyID);

		//getters
		glm::vec2 getMouseCoords() const { return _mouseCoords; }
	private:
		unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;
	};
