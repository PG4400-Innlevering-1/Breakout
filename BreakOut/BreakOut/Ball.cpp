#include "Ball.h"
#include "Window.h"
#define PI 3.14159265


Ball::Ball()
{
	ballDimensions->h = 16;
	ballDimensions->w = 16;
	ballDimensions->x = 160;
	ballDimensions->y = 200;

	mPosX = (SCREEN_WIDTH / 2) - (16 / 2);
	mPosY = 550;

	mVelX = 0;
	mVelY = 0;

	isAttached = true;
	ballSpeed = 200.f;
}


float Ball::getPosX() const
{
	return mPosX;
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
	if (mPosY < 0)
	{
		// entry angle = exit angle
		mVelY = -mVelY;
	}
	else if (mPosX < 0 || SCREEN_WIDTH < mPosX + ballDimensions->w)
	{
		// entry angle = exit angle
		mVelX = -mVelX;
	}
	else if (SCREEN_HEIGHT < mPosY + ballDimensions->h)
	{
		mVelX = 0;
		mVelY = 0;
	}
	else if (paddle.getPosY() < mPosY + ballDimensions->h &&
		paddle.getPosX() < mPosX + ballDimensions->w / 2 &&
		paddle.getPosX() + paddle.paddleDimentions->w > mPosX + ballDimensions->w / 2)
	{
		// returns the point from 22.5 - 157.2 on the paddle left to right
		float pointOnPaddle = mPosX + (ballDimensions->w / 2) + 22.5 - paddle.getPosX();

		// use this point to get a value range(-1, 1) for the velocity x
		mVelX = -ballSpeed*cos(pointOnPaddle * PI / 180);

		// reflect in the opposite direction for the y axis
		mVelY = -mVelY;

		// debug printing
		printf("mVelX = %f, %f, %f\n", mVelX, pointOnPaddle, mVelY);
	}

}

float Ball::getPosY() const
{
	return mPosY;
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
		mPosY += mVelY*deltaTime;
		mPosX += mVelX*deltaTime;

		checkCollision(paddle, deltaTime);
	}
}

void Ball::addInitialVelocity()
{
	if(isAttached)
	{
		mVelY = -200;
	}
}

void Ball::invertY()
{
	mVelY = -mVelY;
}

void Ball::invertX()
{
	mVelX = -mVelX;
}

void Ball::handleEvent(SDL_Event e)
{
	// if a key was pressed
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			addInitialVelocity();
			isAttached = false;
			break;
		}
	}
}

Ball::~Ball()
{
}


