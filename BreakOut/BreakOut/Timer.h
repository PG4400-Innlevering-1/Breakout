#pragma once
#include "../packages/sdl2.v140.2.0.4/build/native/include/SDL_hints.h"

class Timer
{
public:
	Timer();
	~Timer();

	// the clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	// get the timers time
	Uint32 getTicks() const;

	// check the status of the timer
	bool isStarted() const;
	bool isPaused() const;

private:
	// the clock time when the timer started
	Uint32 mStartTicks;

	// the ticks stored when the timer was paused
	Uint32 mPausedTicks;

	// the timer status
	bool mPaused;
	bool mStarted;
};

