#pragma once
class InputManager
{
public:
	InputManager();
	~InputManager();

	enum KeyPresses
	{
		KEY_PRESS_DEFAULT,
		KEY_PRESS_LEFT,
		KEY_PRESS_RIGHT,
		KEY_PRESS_TOTAL
	};

	KeyPresses key;
};

