#pragma once
#include "TextRender.h"
#include "Window.h"	

class HUDManager
{
public:
	HUDManager();
	~HUDManager();

	TextRender livesText;
	TextRender blockCountText;
	TextRender scoreText;

	void drawHUD(SDL_Renderer* renderer);

	void updateHUD(SDL_Renderer* renderer, std::string string);
};

