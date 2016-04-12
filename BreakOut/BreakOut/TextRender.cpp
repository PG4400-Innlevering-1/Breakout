#include "TextRender.h"



TextRender::TextRender()
{
}


TextRender::~TextRender()
{ 

}


bool TextRender::loadTTF_FromString(SDL_Renderer* gRenderer, std::string textureText, SDL_Color textColor)
{
	//Render text surface
	auto* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != nullptr;
}

bool TextRender::loadFont()
{
	//Loading success flag
	auto success = true;

	//Open the font
	font = TTF_OpenFont("res/OpenSans-Regular.ttf", 32);
	if (font == nullptr)
	{
		printf("Failed to load the font SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	return success;
}


void TextRender::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}
