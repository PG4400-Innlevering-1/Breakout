#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"
#include "Ball.h"

const int PIECES = 80;

class Piece
{
public:
	Piece();
	~Piece();

	SDL_Rect* pieceDimentions = new SDL_Rect();
	
	bool isVisible = true;

	void hitByBall(Ball* ball, SDL_Rect rect);
	
};

