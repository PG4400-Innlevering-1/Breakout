#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"
#include "../packages/sdl2_mixer/include/SDL_mixer.h"
#include <stdio.h>
#include <string>	


class BackgroundMusic
{
public:
	BackgroundMusic();
	~BackgroundMusic();

	// The music that will be played
	Mix_Music *gMusic = nullptr;

	static bool init();

	bool loadMedia();

	void play() const;
	static void pause();
	static void resume();

};

