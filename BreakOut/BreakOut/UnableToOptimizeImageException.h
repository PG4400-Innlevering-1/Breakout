#pragma once
#include <exception>


using namespace std;

class UnableToOptimizeImageException : public exception
{
	const char* what() const throw() override
	{
		return "Unable to load image SDL_image";
	}
} UnableToOptimizeImageException;
