#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1;


class Window
{
public:
	Window();
	~Window();


	// The window we'll be rendering to
	SDL_Window* window = nullptr;

	// The surface contained by the window
	SDL_Surface* wSurface = nullptr;

};

