#pragma once
#include <exception>


class ImageNotFoundException : public std::exception
{
	const char* what() const throw() override
	{
		return "Unable to load image SDL_image";
	}
} ImageNotFoundException;
