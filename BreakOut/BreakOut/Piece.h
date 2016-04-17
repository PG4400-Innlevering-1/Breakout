#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"
#include "Ball.h"
#include <memory>

const int PIECES = 80;

class Piece 
{
public:
	Piece();
	~Piece();
	Piece(const Piece &other) noexcept;
	Piece(Piece &&other) noexcept;
	
	// Operator overloading 
	Piece& operator=(Piece&& other) noexcept;
	bool operator!=(const Piece& rhs) const;

	// Smart pointer demonstration
	std::unique_ptr<SDL_Rect> pieceDimentions;

	bool isVisible = true;

	bool hitByBall(Ball* ball, const SDL_Rect rect);
	void reset();
};

