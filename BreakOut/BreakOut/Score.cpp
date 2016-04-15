#include "Score.h"



Score::Score()
{
	score = 0;
}


Score::~Score()
{
}

void Score::addScore()
{
	score += 10;
}

void Score::resetScore()
{
	score = 0;
}
