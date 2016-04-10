#include "BackgroundMusic.h"



BackgroundMusic::BackgroundMusic()
{
}


BackgroundMusic::~BackgroundMusic()
{
	//Free the sound effects
	Mix_FreeChunk(gScratch);
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	gScratch = nullptr;
	gHigh = nullptr;
	gMedium = nullptr;
	gLow = nullptr;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = nullptr;
	
}

bool BackgroundMusic::init()
{
	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not be initialized SDL_Mixer Errror %s\n", Mix_GetError());
		return false;
	}
	return true;
}


// Loads the music
bool BackgroundMusic::loadMedia() 
{
	auto success = true;

	gMusic = Mix_LoadMUS("res/Unreal_Super_Hero_3_by_Kenet_Rez.wav");
	if(gMusic == nullptr)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}else
	{
		play();
	}

	return success;
}

void BackgroundMusic::play() const
{
	Mix_PlayMusic(gMusic, 1);
}

void BackgroundMusic::pause()
{
	Mix_PauseMusic();
}

void BackgroundMusic::resume()
{
	Mix_ResumeMusic();
}