#include <cstdio>
#include "Window.h"
#include "GameManager.h"


int main(int argc, char* argv[])
{
	GameManager game;	

	// initalize the game, return error if fail.
	if (!game.init()) return 1;

	// load the textures into memory, return error if fail
	if (!game.loadMedia()) return 1;


	// Main loop, input/update/draw
	while(game.running())
	{
		game.handleEvents();
		game.tick();
		game.render();
	}

	//In case the main loop ends before the thread finishes, we make a call to SDL_WaitThread
	SDL_WaitThread(game.threadID, nullptr);

	game.close();
	return 0;
}


