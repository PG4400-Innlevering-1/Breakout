#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"
#include "Paddle.h"

class Ball
{
public:
	Ball();
	~Ball();

	// Aka lives
	int ballsLeft = 3;
	bool bUpdateHUD = true;

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

	int getLivesLeft() const { return ballsLeft; };

	void attachBall();
	
private:
	float mBallSpeed;

	float mPosX, mPosY;

	float mVelX, mVelY;

	float mTinyOffset = 0.00025;

	bool isAttached;

	float velocity = 200;

};

