#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL.h"
#include <string>
#include "MediaManager.h"

class Texture
{
public:
	Texture();
	~Texture();

	// destroy the texture
	void free();

	// renders the texture to the given point
	void render(float x, float y, struct SDL_Rect* clip, SDL_Renderer* gRenderer) const;

	// get the image dimetions
	int getWidth() const;
	int getHeigth() const;

	// loads the image
	bool loadTexture(std::string path, SDL_Renderer* gRenderer);


private:
	// image dimentions
	int mWidth;
	int mHeight;

	// the sprite sheet
	SDL_Texture* gTexture = nullptr;
};

