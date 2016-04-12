#include "HUDManager.h"



HUDManager::HUDManager()
{
}


HUDManager::~HUDManager()
{
}

void HUDManager::drawHUD(SDL_Renderer* renderer)
{
	scoreText.render(renderer, SCREEN_WIDTH - scoreText.getWidth(), SCREEN_HEIGHT - scoreText.getHeight());
	livesText.render(renderer, 0, SCREEN_HEIGHT - livesText.getHeight());
	blockCountText.render(renderer, SCREEN_WIDTH - scoreText.getWidth() / 2, SCREEN_HEIGHT - scoreText.getHeight() / 2);
}


