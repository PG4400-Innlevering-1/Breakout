#pragma once
#include <SDL.h>
#include "Window.h"
#include "Texture.h"
#include "Paddle.h"
#include <chrono>
#include "Timer.h"
#include "Ball.h"
#include "Piece.h"
#include <array>
#include "BackgroundMusic.h"
#include "InputManager.h"
#include "TextRender.h"

using namespace std;

class GameManager
{
public:
	GameManager();
	~GameManager();

	// The window we will draw to
	Window window;

	bool loadMedia();

	// general setup for the game
	bool init();

	// for when we want to pause
	void pause();

	// no longer paused
	void resume();

	// Update the UI/HUD
	void updateHUD();
	
	// handle input
	void handleEvents();

	// update/tick takes care of the game logic
	void tick();

	// takes care of the rendering to the screen
	void render();

	// close the game and clean up
	void close();

	// check if we are still running
	bool running() const { return mRunning; }
	void quit() { mRunning = false; }

	// Event handler
	SDL_Event event;

	// Paddle
	Paddle paddle;

	// Ball
	Ball ball;

	// the pieces
	array<Piece, sizeof(Piece)*PIECES> pieces;

	// Game timers
	typedef chrono::high_resolution_clock hr_clock;
	typedef hr_clock::time_point time_point;
	typedef hr_clock::duration duration;
	time_point currentFrame = hr_clock::now();

	Uint32 startTime;
	float deltaTime;

	//The frames per second timer
	Timer fpsTimer;

	//The frames per second cap timer
	Timer capTimer;

	int countedFrames = 0;

	// Input Manager
	InputManager inputManager;

	// Audio
	BackgroundMusic bgMusic;
	
	// Screen Text HUD
	TextRender textRender;
	

private:
	bool mRunning;

	// Our renderer
	SDL_Renderer* gRenderer = nullptr;
	
	// My own texture class wraper that hold the sprite sheet
	Texture spriteSheet;
	Texture gTexture;

	int level = 0;
	int totalBlocksDestroyed = 0;

	void nextLevel();

	static void initBlocks(array<Piece, sizeof(Piece)*PIECES> pieces, int level);
};

