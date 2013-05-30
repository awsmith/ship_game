#include "timer.h"

// Default constructor
Timer::Timer()
{
	// Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

// Start the timer set startTicks
void Timer::start()
{
	// Start the timer
	started = true;

	// Unpause the timer
	paused = false;

	// Get the current clock timer
	startTicks = SDL_GetTicks();
}

// Stop and reset the timer
void Timer::stop()
{
	// Stop the timer
	started = false;

	// Unpause the timer
	paused = false;
}

// Return the current ticks if paused or running
int Timer::get_ticks()
{
	// If the timer is running
	if(started == true)
	{
		// If the timer is paused
		if(paused == true)
		{
			// Return the number of ticks when the timer was paused
			return pausedTicks;
		}
		else
		{
			// Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}

	// If the timer isn't running
	return 0;
}

// Pause the timer and set pausedTicks
void Timer::pause()
{
	// If the timer is running and isn't already paused
	if((started == true) && (paused == false))
	{
		// Pause the timer
		paused = true;

		// Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

// Unpause the timer, set startTicks and clear pausedTicks
void Timer::unpause()
{
	// If the timer is paused
	if(paused == true)
	{
		// Unpause the timer
		paused = false;
		
		// Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		// Reset the paused ticks
		pausedTicks = 0;
	}
}

// Check if timer is running
bool Timer::is_started()
{
	return started;
}

// Check if timer is paused
bool Timer::is_paused()
{
	return paused;
}
