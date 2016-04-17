#include "Piece.h"
#include <array>


Piece::Piece() : pieceDimentions(new SDL_Rect())
{
	pieceDimentions->h = 30;
	pieceDimentions->w = 50;
}


Piece::~Piece()
{
}

// Copy constructor
Piece::Piece(const Piece &other) noexcept : pieceDimentions( new SDL_Rect(*other.pieceDimentions))
{
	isVisible = other.isVisible;
	printf("Copy constructor called\n");
}

// Mostly to demostrate move semantics in c++, couldn't find any other good use case for it
// but i think this will demonstate it pretty good
Piece::Piece(Piece &&other) noexcept
{
	isVisible = std::move(other.isVisible);
	pieceDimentions = std::move(other.pieceDimentions);
	other.reset();
	printf("Move Constructer called\n");
}

// Move assinment operator
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
		pieceDimentions->w != rhs.pieceDimentions->w ||
		pieceDimentions->h != rhs.pieceDimentions->h ||
		pieceDimentions->x != rhs.pieceDimentions->x ||
		pieceDimentions->y != rhs.pieceDimentions->y ||
		isVisible != rhs.isVisible;
}

bool Piece::hitByBall(Ball *ball, const SDL_Rect rect)
{
	auto collision = SDL_HasIntersection(&rect, pieceDimentions.get());
	
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

// Smart pointer dereference and list initialization
void Piece::reset()
{
	isVisible = true;
	if (pieceDimentions != nullptr) 
	{
		*pieceDimentions = {
			pieceDimentions->h = 30,
			pieceDimentions->w = 50,
			pieceDimentions->x = 0,
			pieceDimentions->y = 0
		};
	}
}
