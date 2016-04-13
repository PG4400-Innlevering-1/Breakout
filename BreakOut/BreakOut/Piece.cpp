#include "Piece.h"
#include <array>


Piece::Piece()
{
	pieceDimentions->h = 30;
	pieceDimentions->w = 50;
}


Piece::~Piece()
{
}

bool Piece::hitByBall(Ball *ball, const SDL_Rect rect)
{
	auto collision = SDL_HasIntersection(&rect, pieceDimentions);
	
	if(collision)
	{
		if (isVisible)
		{
			printf("Inverty Y...\n");
			ball->invertY();
		}
		isVisible = false;
	}

	return collision;
}

void Piece::free()
{
	delete pieceDimentions;
}
