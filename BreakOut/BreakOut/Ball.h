#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"
#include "Paddle.h"

class Ball
{
public:
	Ball();
	~Ball();

	SDL_Rect* ballDimensions = new SDL_Rect();

	float getPosX() const;
	float getPosY() const;
	float getVelX() const;
	float getVelY() const;

	void checkCollision(const Paddle paddle, const double deltaTime);
	void move(const Paddle paddle, const double deltaTime);
	void addInitialVelocity();

	void handleEvent(SDL_Event e);

	void invertY();
	void invertX();
private:
	float ballSpeed;

	float mPosX, mPosY;

	float mVelX, mVelY;

	bool isAttached;

};

