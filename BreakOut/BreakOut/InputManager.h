#pragma once
#include <cstddef>
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	const Uint8* keys;
	int numKeys; 
				

	enum KeyPresses
	{
		KEY_PRESS_DEFAULT,
		KEY_PRESS_LEFT,
		KEY_PRESS_RIGHT,
		KEY_PRESS_TOTAL
	};

};

