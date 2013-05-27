#include <iostream>
#include "utils.h"
#include "ship.h"

// Game constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 30;

// Game surfaces
SDL_Surface *screen = NULL;

// Events
SDL_Event event;

// Classes
// TODO: Remove timer from game.cpp and creater Timer header and implementation file
class Timer
{
  public:
// Default constructor
  Timer();

	// The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	// Get the timer's time
	int get_ticks();

	// Checks the status of the timer
	bool is_started();
	bool is_paused();

	private:
	// The time when the timer startered
	int startTicks;

	// The ticks stored when the timer was paused
	int pausedTicks;

	// The timer status
	bool paused;
	bool started;
};

int main()
{
	// Quit flag for event loop
	bool quit = false;

	// Initialize SDL systems and screen
	// TODO: Change init function to bool and pass screen as a reference to a pointer
	screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screen);

	// If init failed to initialize everything
	if(screen == NULL)
	{
		return 0;
	}

	// Class instances
	ship myShip;
	Timer fps;

	// While the user has not quit
	while(quit == false)
	{
		// Start the fps timer
		fps.start();

		while(SDL_PollEvent(&event))
		{
			// Handle input from user. Only accepts up, down, left and right keys currently.
			myShip.handle_input(event);

			// If the user X's out the window
			if(event.type == SDL_QUIT)
			{
				// Exit event loop
				quit = true;
			}
		}

		// Make the screen white
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0xFF, 0xFF ) );

		// Adjust the x and y coordinates of the ship and apply to screen
		myShip.move();
		myShip.show(screen);

		// TODO: Apply player and generated prjoectiles

		// TODO: Apply enemy and generated projectiles

		// Refresh screen
		if(SDL_Flip(screen) == -1)
		{
			return 0;
		}

		// Cap the frame rate if game is running too fast
		if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}
	SDL_Quit;
	return 0;
}

// TODO: Remove once Timer header and implementation files have been created
Timer::Timer()
{
	// Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start()
{
	// Start the timer
	started = true;

	// Unpause the timer
	paused = false;

	// Get the current clock time
	startTicks =SDL_GetTicks();
}

void Timer::stop()
{
	// Stop the timer
	started = false;

	// Unpause the timer
	paused = false;

}

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

void Timer::unpause()
{
	// If the timer is paused
	if(paused == true)
	{
		// Unpaused the timer
		paused = false;

		// Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		// Reset the paused ticks
		pausedTicks = 0;
	}
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused;
}
