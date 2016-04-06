#include "Texture.h"
#include <SDL_image.h>


Texture::Texture()
{
}



void Texture::free()
{
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;
}


Texture::~Texture()
{
}


int Texture::getWidth() const
{
	return mWidth;
}


int Texture::getHeigth() const
{
	return mWidth;
}


void Texture::render(float x, float y, struct SDL_Rect* clip, SDL_Renderer* gRenderer) const
{
	// set the rendering space and render to screen
	SDL_Rect renderingQuad = { x, y, mWidth, mHeight };

	// Set clip rendering dimetsions
	if( clip != nullptr ) 
	{
		renderingQuad.w = clip->w;
		renderingQuad.h = clip->h;
	}

	// render to screen
	SDL_RenderCopy(gRenderer, gTexture, clip, &renderingQuad);
}


bool Texture::loadTexture(std::string path, SDL_Renderer* gRenderer)
{
	// the final texture
	SDL_Texture* texture = nullptr;

	// load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s SDL_image ERROR: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (texture == nullptr)
		{
			printf("Unable to optimize image %s! SDL ERROR %s\n", path.c_str(), SDL_GetError());
		}
		// get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	gTexture = texture;

	return gTexture != nullptr;
}

