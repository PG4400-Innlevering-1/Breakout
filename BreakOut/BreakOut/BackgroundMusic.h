#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>	


class BackgroundMusic
{
public:
	BackgroundMusic();
	~BackgroundMusic();

	// The music that will be played
	Mix_Music *gMusic = nullptr;

	// the sound effect taht will be used
	Mix_Chunk *gScratch = nullptr;
	Mix_Chunk *gHigh = nullptr;
	Mix_Chunk *gMedium = nullptr;
	Mix_Chunk *gLow = nullptr;

	static bool init();

	bool loadMedia();

	void play() const;
	static void pause();
	static void resume();

};

