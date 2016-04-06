#include "Timer.h"
#include <SDL.h>


Timer::Timer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}


void Timer::start()
{
	// starts the timer
	mStarted = true;

	// Unpause the timer 
	mPaused = false;

	// get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	mStarted = false;

	mPaused = false;

	// clear the tick vars
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	// if the timer is running and isnt already paused
	if(mStarted && !mPaused)
	{
		// pause the timer
		mPaused = true;

		// calculate the pused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	if(mStarted && mPaused)
	{
		// unpause
		mPaused = false;

		// reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		// reset the paused ticks
		mPaused = 0;
	}
}

Uint32 Timer::getTicks() const
{
	// the actual timer time
	Uint32 time = 0;

	// if the timer is running
	if(mStarted)
	{
		if(mPaused)
		{
			// return the numer of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			// return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
}

bool Timer::isStarted() const
{
	return mStarted;
}

bool Timer::isPaused() const
{
	return mPaused;
}

Timer::~Timer()
{
}
