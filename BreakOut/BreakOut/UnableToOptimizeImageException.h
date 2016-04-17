#pragma once
#include <exception>


class UnableToOptimizeImageException : public std::exception
{
	const char* what() const throw() override
	{
		return "Unable to optimize image SDL ERROR";
	}
} UnableToOptimizeImageException;
