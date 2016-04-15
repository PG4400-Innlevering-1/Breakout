#include "Piece.h"
#include <array>


Piece::Piece()
{
	pieceDimentions.h = 30;
	pieceDimentions.w = 50;
}


Piece::~Piece()
{
}

Piece::Piece(Piece &&other) noexcept
{
	isVisible = std::move(other.isVisible);
	pieceDimentions = std::move(other.pieceDimentions);
	other.reset();
	printf("Move Constructer called\n");
}


Piece& Piece::operator=(Piece&& other) noexcept
{
	if(this != &other)
	{
		pieceDimentions = std::move(other.pieceDimentions);
		isVisible = std::move(other.isVisible);
		other.reset();
	}

	printf("Move assignement operator called\n");

	return *this;
}

bool Piece::operator!=(const Piece& rhs) const
{
	return
		pieceDimentions.w != rhs.pieceDimentions.w ||
		pieceDimentions.h != rhs.pieceDimentions.h ||
		pieceDimentions.x != rhs.pieceDimentions.x ||
		pieceDimentions.y != rhs.pieceDimentions.y ||
		isVisible != rhs.isVisible;
}

bool Piece::hitByBall(Ball *ball, const SDL_Rect rect)
{
	auto collision = SDL_HasIntersection(&rect, &pieceDimentions);
	
	if(collision)
	{
		if (isVisible)
		{
			ball->invertY();
		}
		isVisible = false;
	}

	return collision;
}

void Piece::reset()
{
	isVisible = true;
	pieceDimentions = {
		pieceDimentions.h = 30, 
		pieceDimentions.w = 50, 
		pieceDimentions.x = 0, 
		pieceDimentions.y = 0 
	};
}
