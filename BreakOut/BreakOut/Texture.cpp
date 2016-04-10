#include "Texture.h"
#include <stdexcept>
#include <SDL_image.h>
#include <iostream>
#include <exception>
#include "ImageNotFound.h"

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


bool Texture::loadTexture(const std::string path, SDL_Renderer* gRenderer) 
{
	// the final texture
	SDL_Texture* texture = nullptr;
	
	try {
		// load image at specified path
		auto* loadedSurface = IMG_Load(path.c_str());

		if (loadedSurface == nullptr) {
			printf("Unable to load image %s SDL_image ERROR: %s\n", path.c_str(), IMG_GetError());
			throw ImageNotFound;
		}

		// Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (texture == nullptr) {
			printf("Unable to optimize image %s! SDL ERROR %s\n", path.c_str(), SDL_GetError());
		}

		// get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

	} catch(exception& e) {

		cout << "Unable to Load texture, ERROR NUMBER: " << e.what() << endl;
	}

	gTexture = texture;

	return gTexture != nullptr;
}

