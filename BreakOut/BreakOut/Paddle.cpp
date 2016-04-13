#include "Paddle.h"


Paddle::Paddle()
{
	paddleDimentions->h = 30;
	paddleDimentions->w = 135;
	paddleDimentions->x = 0;
	paddleDimentions->y = 280;

	mPosX = (SCREEN_WIDTH / 2) - (135 / 2);
	mPosY = 570;

	mVelX = 0;
	mVelY = 0;
}


float Paddle::getPosX() const
{
	return mPosX;
}

float Paddle::getPosY() const
{
	return mPosY;
}

float Paddle::getVelX() const
{
	return mVelX;
}

float Paddle::getVelY() const
{
	return mVelY;
}

Paddle::~Paddle()
{
}

void Paddle::move(double deltaTime)
{
	// move the paddle left or right
	mPosX += mVelX*deltaTime;

	// if the paddle went too far to the left or right
	if(mPosX < 0)
	{
		mPosX = 0;
	}
	else if(mPosX + paddleDimentions->w > SCREEN_WIDTH)
	{
		mPosX = SCREEN_WIDTH - paddleDimentions->w;
	}
}

void Paddle::movePaddleLeft()
{
	 if(mPosX > 0)
	{
		mVelX -= VELOCITY;
	} 

	if(mPosX <= 0)
	{
		mVelX = 0;
	}
}

void Paddle::movePaddleRight()
{
	if (mPosX + paddleDimentions->w < SCREEN_WIDTH)
	{
		mVelX += VELOCITY;
	}

	// Paddle has hit a wall
	if(mPosX + paddleDimentions->w >= SCREEN_WIDTH)
	{
		mVelX = 0;
	}
}

void Paddle::free() const
{
	delete paddleDimentions;
}

void Paddle::handleEvent(const InputManager input)
{
	// state snapshot
	if(input.keys[SDL_SCANCODE_LEFT])
	{ 
		movePaddleLeft();
	}
	else if(input.keys[SDL_SCANCODE_RIGHT])
	{
		movePaddleRight();
	}
	else
	{
		mVelX = 0;
	}
}
