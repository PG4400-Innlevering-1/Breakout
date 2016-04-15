#include "Texture.h"
#include <stdexcept>
#include <SDL_image.h>
#include <iostream>
#include <exception>
#include "ImageNotFoundException.h"
#include "UnableToOptimizeImageException.h";

using namespace std;

Texture::Texture(): mWidth(0), mHeight(0) {
}



void Texture::free() {
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;
}


Texture::~Texture() {
}


int Texture::getWidth() const {
	return mWidth;
}


int Texture::getHeigth() const {
	return mWidth;
}


void Texture::render(const float x, const float y, const SDL_Rect* clip, SDL_Renderer* gRenderer) const 
{
	// set the rendering space and render to screen
	SDL_Rect renderingQuad = { x, y, mWidth, mHeight };

	// Set clip rendering dimetsions
	if( clip != nullptr ) {
		renderingQuad.w = clip->w;
		renderingQuad.h = clip->h;
	}

	// render to screen
	SDL_RenderCopy(gRenderer, gTexture, clip, &renderingQuad);
}

// Demonstrating exception handling by making my own exceptions
bool Texture::loadTexture(const std::string path, SDL_Renderer* gRenderer) 
{
	// the final texture
	SDL_Texture* texture = nullptr;
	
	// load image at specified path
	auto* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) 
	{	
		throw ImageNotFoundException;
	}

	// Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (texture == nullptr) 
	{
		throw UnableToOptimizeImageException; 
	}

	// get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	gTexture = texture;

	return gTexture != nullptr;
}

