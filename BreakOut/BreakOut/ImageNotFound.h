#pragma once
#include <exception>

using namespace std;

class ImageNotFound : public exception
{
	const char* what() const throw() override
	{
		return "Image file not found, check the res folder";
	}
} ImageNotFound;
