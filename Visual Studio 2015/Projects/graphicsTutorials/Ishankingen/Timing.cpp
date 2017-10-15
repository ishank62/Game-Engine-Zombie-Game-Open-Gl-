#include "Timing.h"
#include <SDL/SDL.h>


	FpsLimiter::FpsLimiter(){}

	void FpsLimiter::init(float maxFPS){
		setMaxFps(maxFPS);
	}

	void FpsLimiter::setMaxFps(float maxFPS){
		_maxFPS = maxFPS;
	}

	void FpsLimiter::begin(){
		_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::end(){
		calculateFPS();
		//Limiter
		float frameTicks = SDL_GetTicks() - _startTicks;
		if ((1000.0f / _maxFPS) > frameTicks) {
			SDL_Delay((1000.0f / _maxFPS) - frameTicks);
		}
		return _fps;
	}

	void FpsLimiter::calculateFPS() {
		static const int numSamples = 10;
		static float frameTimes[numSamples];
		static int currentFrame = 0;

		static float prevTicks = SDL_GetTicks();
		float currentTicks = SDL_GetTicks();

		_frameTime = currentTicks - prevTicks;

		frameTimes[currentFrame%numSamples] = _frameTime;

		prevTicks = currentTicks;

		int count;
		currentFrame++;
		if (currentFrame < numSamples) {
			count = currentFrame;
		}
		else {
			count = numSamples;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0) {
			_fps = 1000.0f / frameTimeAverage;
		}
		else {
			_fps = 60.0f;
		}
	}
	
