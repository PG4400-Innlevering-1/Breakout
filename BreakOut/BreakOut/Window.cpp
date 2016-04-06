#include "Window.h"



Window::Window()
{
}


Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_FreeSurface(wSurface);
}
