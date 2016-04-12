#include "InputManager.h"



InputManager::InputManager()
{
	// Initialiser key state-pekeren
	keys = SDL_GetKeyboardState(&numKeys);
}


InputManager::~InputManager()
{
}
