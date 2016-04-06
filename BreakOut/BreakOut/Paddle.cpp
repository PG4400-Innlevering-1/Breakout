#include "Paddle.h"
#include "Window.h"

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

void Paddle::free() const
{
	delete paddleDimentions;
}

void Paddle::handleEvent(SDL_Event e)
{

	// if a key was pressed
	if(e.type == SDL_KEYDOWN)
	{
		switch(e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mVelX -= VELOCITY;
			break;
		case SDLK_RIGHT:
			mVelX += VELOCITY;
			break;
		} 
	}  
	else
	{
		mVelX = 0;
	}
	
}
