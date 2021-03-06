#include "Ball.h"



Ball::Ball()
{
	mCollider.h = 16;
	mCollider.w = 16;
	mCollider.x = 160;
	mCollider.y = 200;

	mPosX = (SCREEN_WIDTH / 2) - (16 / 2);
	mPosY = 550;

	mVelX = 0;
	mVelY = 0;

	isAttached = true;
	mBallSpeed = 2.f;
}


float Ball::getPosX() const
{
	return mPosX;
}

float Ball::getPosY() const
{
	return mPosY;
}

float Ball::getVelX() const
{
	return mVelX;
}

float Ball::getVelY() const
{
	return mVelY;
}

void Ball::checkCollision(const Paddle paddle, const double deltaTime)
{
	// Wall collision
	if (mPosY < 0)								// top wall
	{
		// entry angle = exit angle
		mVelY = velocity;
	}
	else if (mPosX < 0)							// left wall
	{
		// entry angle = exit angle
		mVelX = abs(mVelX);
	}
	else if(SCREEN_WIDTH < mPosX + mCollider.w) // right wall
	{
		mVelX = -abs(mVelX);
	}
												// Ball hits the floor
	else if ((SCREEN_HEIGHT - 50) < mPosY + mCollider.h)
	{
		mLives--;
		isAttached = true;
		mVelX = 0;
		mVelY = 0;
	}
	else if (paddle.getPosY() < mPosY + mCollider.h &&
		paddle.getPosX() < mPosX + mCollider.w / 2 &&
		paddle.getPosX() + paddle.paddleDimentions.w > mPosX + mCollider.w / 2)
	{
		// returns the point from 22.5 - 157.2 on the paddle left to right
		float pointOnPaddle = mPosX + (mCollider.w / 2) + 22.5 - paddle.getPosX();

		// use this point to get a value range(-1, 1) for the velocity x
		mVelX = -velocity*cos(pointOnPaddle * M_PI / 180);

		// reflect in the opposite direction for the y axis
		mPosY -= 0.5;
		mVelY = -mVelY;
	}
}


void Ball::move(const Paddle paddle, const double deltaTime)
{
	if(isAttached)
	{
		// make the ball follow the paddle
		mPosX = paddle.getPosX() + 135/2 - 8;
		mPosY = paddle.getPosY() - 16;
	}
	else
	{
		// physics engine really simple
		mPosY += mVelY*deltaTime*mBallSpeed;
		mPosX += mVelX*deltaTime*mBallSpeed;

		checkCollision(paddle, deltaTime);
	}
}

void Ball::addInitialVelocity()
{
	if(isAttached)
	{
		mVelY = -velocity;
	}
	isAttached = false;
}

void Ball::invertY() 
{
	mVelY = -mVelY;
}

void Ball::invertX()
{
	mVelX = -mVelX;
}

void Ball::handleEvent(const SDL_Event e)
{
	// if a key was pressed
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
				addInitialVelocity();		
				break;
		}
	}
}

void Ball::attachBall()
{
	isAttached = true;
}


Ball::~Ball()
{
}


