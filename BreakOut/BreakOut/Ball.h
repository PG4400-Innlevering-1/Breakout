#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"
#include "Paddle.h"
#include "Window.h"
#include <cmath>

class Ball
{
public:
	Ball();
	~Ball();

	// Players lives 
	int mLives = 3;

	// Bounding box
	SDL_Rect mCollider;

	float getPosX() const;
	float getPosY() const;
	float getVelX() const;
	float getVelY() const;

	void checkCollision(const Paddle paddle, const double deltaTime);
	void move(const Paddle paddle, const double deltaTime);
	void addInitialVelocity();

	void handleEvent(const SDL_Event e);

	void invertY();
	void invertX();

	int getLivesLeft() const { return mLives; }
	void setLives(const int lives) { mLives = lives; }

	void attachBall();
	
private:
	float mBallSpeed;

	float mPosX, mPosY;

	float mVelX, mVelY;

	bool isAttached;

	float velocity = 200;

};

