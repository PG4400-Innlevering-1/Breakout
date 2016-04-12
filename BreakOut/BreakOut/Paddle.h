#pragma once
#include "Texture.h"
#include "InputManager.h"
#include "Window.h"

class Paddle
{
public:
	Paddle();
	~Paddle();

	SDL_Rect* paddleDimentions = new SDL_Rect();

	const float VELOCITY = 1000;

	float getPosX() const;
	float getPosY() const;
	float getVelX() const;
	float getVelY() const;

	void move(double deltaTime);

	void free() const;

	void handleEvent(const InputManager input);

	void movePaddleRight();
	void movePaddleLeft();


private:
	// Position
	float mPosX, mPosY;

	// Velocity
	float mVelX, mVelY;
};

