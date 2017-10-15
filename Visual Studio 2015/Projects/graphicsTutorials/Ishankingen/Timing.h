#pragma once


class FpsLimiter {
public:
	FpsLimiter();
	void init(float maxFPS);
	void setMaxFps(float maxFPS);

	void begin();

	float end();//returns current FPS
private:

	void calculateFPS();
	float _fps;
	float _frameTime;
	float _maxFPS;
	unsigned int _startTicks;
}; 
