#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>


class TextRender
{
public:
	TextRender();
	~TextRender();
	
	SDL_Texture* mTexture = nullptr;

	// loads the texture from the text string
	bool loadTTF_FromString(SDL_Renderer* gRenderer, std::string textureText, SDL_Color textColor);
	
	// Loads the font from file
	bool loadFont();

	// The font
	TTF_Font *font = nullptr;

	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr,
		double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip = SDL_FLIP_NONE) const;

	int getWidth() const { return mWidth; };
	int getHeight() const { return mHeight; };

	void free();

private:	

	//Image dimensions
	int mWidth;
	int mHeight;
};

