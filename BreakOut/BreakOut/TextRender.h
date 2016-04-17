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

	// The font
	TTF_Font *font = nullptr;

	// loads the texture from the text string
	bool loadTTF_FromString(SDL_Renderer* const gRenderer, const std::string textureText, const SDL_Color textColor);
	
	// Loads the font from file
	bool loadFont();

	void render(SDL_Renderer* const renderer, const int x, const int y, const SDL_Rect* clip = nullptr,
		const double angle = 0.0, const SDL_Point* center = nullptr, const SDL_RendererFlip = SDL_FLIP_NONE) const;

	int getWidth() const { return mWidth; };
	int getHeight() const { return mHeight; };

	void free();

private:	

	//Image dimensions
	int mWidth;
	int mHeight;
};

