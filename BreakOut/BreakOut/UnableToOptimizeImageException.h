#pragma once
#include <exception>


using namespace std;

class UnableToOptimizeImageException : public exception
{
	const char* what() const throw() override
	{
		return "Unable to optimize image SDL ERROR";
	}
} UnableToOptimizeImageException;
