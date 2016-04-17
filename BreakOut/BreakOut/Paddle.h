#pragma once
#include "Texture.h"
#include "InputManager.h"
#include "Window.h"

class Paddle
{
public:
	Paddle();
	~Paddle();

	SDL_Rect paddleDimentions;

	const float VELOCITY = 1000;

	float getPosX() const;
	float getPosY() const;
	float getVelX() const;
	float getVelY() const;

	void move(const double deltaTime);

	void handleEvent(const InputManager input);

	void movePaddleRight();
	void movePaddleLeft();

private:
	// Position
	float mPosX, mPosY;

	// Velocity
	float mVelX, mVelY;
};

