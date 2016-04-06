#pragma once
#include "Texture.h"

class Paddle
{
public:
	Paddle();
	~Paddle();

	SDL_Rect* paddleDimentions = new SDL_Rect();

	const float VELOCITY =	10;

	float getPosX() const;
	float getPosY() const;
	float getVelX() const;
	float getVelY() const;


	void move(double deltaTime);

	void free() const;

	void handleEvent(SDL_Event e);

	

private:
	// Position
	float mPosX, mPosY;

	// Velocity
	float mVelX, mVelY;
};

