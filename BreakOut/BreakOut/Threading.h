#pragma once
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <iostream>
#include "Ball.h"
#include <thread>

static bool threadRunning = true;

class Threading
{
public:
	Threading();
	~Threading();

	// My test thread/template function
	static int threadedFunction(void* data);

	template <class T>
	static void genericThreadFunction(T &data);
	
	template <class T>
	static T const& max(T const& a, T const& b);
		
	static void stdThreadFunction(Ball* ball);

	static void endThread();

};



