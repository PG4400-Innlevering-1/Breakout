#include <stdexcept>
#include "GameManager.h"
#include "../packages/sdl2_image.v140.2.0.1/build/native/include/SDL_image.h"
#include <iostream>
#include "../packages/sdl2_ttf.v140.2.0.14/build/native/include/SDL_ttf.h"

GameManager::GameManager() : mRunning(true) {
	fpsTimer.start();
}


bool GameManager::loadMedia()
{
	// load success flag
	auto success = true;

	bool isLoaded;

	isLoaded = spriteSheet.loadTexture("res/breakout_sprites.png", gRenderer);
	if (!isLoaded) {
		printf("Failed to load sprite sheet image\n");
		success = false;
	}

	isLoaded = bgMusic.loadMedia();
	if (!isLoaded)
	{
		printf("Failed to load music\n");
		success = false;
	}


	isLoaded = textRender.loadFont();
	if (!isLoaded)
	{
		printf("Failed to load the font");
	}
	return success;
}


bool GameManager::init()
{
	// success flag
	auto success = true;

	// init SDL video and audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize SDL ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// create the window
		window.window = SDL_CreateWindow("Breakout",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
			);

		if (window.window == nullptr) {
			printf("Window could not be created SDL ERROR: %s\n", SDL_GetError());
			success = false;

		}
		else
		{
			// create the renderer for the window
			gRenderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == nullptr)
			{
				printf("Renderer could not be created SDL ERROR %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// init png loading
				int imgFlags = IMG_INIT_PNG;

				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_Image could not be initalized, SDL_Image ERROR: %s\n", IMG_GetError());
					success = false;
				}
				else {
					// init SDL_mixer
					success = bgMusic.init();
				}
			}
		}
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	// initialize the pieces level 0
	initBlocks(pieces, level);

	return success;
}


void GameManager::pause()
{
	bgMusic.pause;
}

void GameManager::resume() 
{
	bgMusic.resume;
}

void GameManager::updateHUD()

{
	int score = getScore();
	if (ball.bUpdateHUD)
	{
		ball.bUpdateHUD = false;
		SDL_Color color{ color.r = 0xff, color.g = 0xff, color.b = 0xff, color.a = 0xff };
		string str = "";
		for (auto i = 0; i < ball.getLivesLeft(); i++)
		{
			str += "<3";
		}

		textRender.loadTTF_FromString(gRenderer, "Lives: " + str + "Score: " + score, color);
		
	}
}


void GameManager::handleEvents()
{


	//Handle events on queue
	while (SDL_PollEvent(&event) != 0) {

		//User requests quit
		if (event.type == SDL_QUIT) {
			mRunning = false;
		}
	}

	paddle.handleEvent(inputManager);
	ball.handleEvent(event);
}


void GameManager::tick()
{
	capTimer.start();

	// Calcuclate delta time
	auto lastFrame = currentFrame;
	currentFrame = hr_clock::now();
	auto timeSpan = currentFrame - lastFrame;
	deltaTime = static_cast<float>(timeSpan.count()) / 1000000000.0f;

	//Calculate and correct fps
	auto avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);

	if (avgFPS > 2000000) {

		avgFPS = 0;
	}

	/***************
	* Movement
	****************/

	paddle.move(deltaTime);
	ball.move(paddle, deltaTime);

	SDL_Rect ballRect;
	ballRect.x = ball.getPosX();
	ballRect.y = ball.getPosY();
	ballRect.w = ball.mCollider.w;
	ballRect.h = ball.mCollider.h;

	// Check collision with the pieces
	for (auto & piece : pieces)
	{
		if (piece.isVisible)
		{
			auto hit = piece.hitByBall(&ball, ballRect);
			// We do not want to have more than 1 collision per frame
			if (hit) {
				totalBlocksDestroyed++;
				score++;
				updateScore(score);
				break;
			}
		}
	}

	if (totalBlocksDestroyed == PIECES)
	{
		nextLevel();
	}

	// Update the Game HUD
	updateHUD();

	// Game over
	if (ball.getLivesLeft() == 0)
	{
		quit();
	}

	int frameTicks = capTimer.getTicks();
	if (frameTicks < SCREEN_TICKS_PER_FRAME)
	{
		// wait the remaining time
		SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
	}

}


void GameManager::render()
{
	// Cool random color background
	srand(time(nullptr));
	auto random1 = static_cast<double>(rand()) / (RAND_MAX)+1;
	auto random2 = static_cast<double>(rand()) / (RAND_MAX)+1;
	auto random3 = static_cast<double>(rand()) / (RAND_MAX)+1;

	// Render background
	SDL_SetRenderDrawColor(gRenderer,
		random1 * 255,
		random2 * 255,
		random3 * 255,
		0xff
		);

	// Clear the screen
	SDL_RenderClear(gRenderer);

	// render the bottom bar
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
	SDL_Rect rect{ rect.x = 0, rect.y = SCREEN_HEIGHT - 50, rect.h = 50, rect.w = SCREEN_WIDTH };
	SDL_RenderFillRect(gRenderer, &rect);

	// render the paddle
	spriteSheet.render(paddle.getPosX(), paddle.getPosY(), paddle.paddleDimentions, gRenderer);

	// render the ball
	spriteSheet.render(ball.getPosX(), ball.getPosY(), &ball.mCollider, gRenderer);

	textRender.render(gRenderer, 0, SCREEN_HEIGHT - textRender.getHeight());

	// render pieces
	for (auto i = 0; i < PIECES; i++)
	{
		switch (i % 5)
		{
			case 0:
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 255);
			break;
			case 1:
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			break;
			case 2:
			SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
			break;
			case 3:
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
			break;
			case 4:
			SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 255);
			break;
			default:
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
			break;
		}

		// only if they're not hit
		if (pieces[i].isVisible) {
			SDL_RenderFillRect(gRenderer, pieces[i].pieceDimentions);
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
			SDL_RenderDrawRect(gRenderer, pieces[i].pieceDimentions);
		}
	}
	// Update screen
	SDL_RenderPresent(gRenderer);
}


void GameManager::close() {


	// free loaded images
	gTexture.free();
	spriteSheet.free();

	// destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	// quit subsystems
	//Free global font
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void GameManager::nextLevel()
{
	totalBlocksDestroyed = 0;
	level++;
	ball.attachBall();
	for (auto & piece : pieces)
	{
		piece.isVisible = true;
	}

	initBlocks(pieces, level);
}

void GameManager::initBlocks(array<Piece, sizeof(Piece)*PIECES> pieces, int level)
{
	for (auto i = level; i < PIECES; i++)
	{
		pieces[i].pieceDimentions->x = i % 16 * pieces[i].pieceDimentions->w;
		pieces[i].pieceDimentions->y = i % 5 * pieces[i].pieceDimentions->h;
	}
}

int getScore() 
{
	return score;
}

GameManager::~GameManager()
{
}
