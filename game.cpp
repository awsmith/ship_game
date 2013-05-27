#include <iostream>
#include "utils.h"
#include "ship.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 20;
SDL_Surface *screen = NULL;
SDL_Event event;


// Classes
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
	SDL_Event event;	
	bool quit = false;

	screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screen);

	ship myShip;
	Timer fps;
	fps.start();

	if(screen == NULL)
	{
		return 0;
	}

	while(quit == false)
	{
		while(SDL_PollEvent(&event))
		{
			// ship input
			if(event.type == SDL_QUIT)
			{
				quit = true;
			}
			myShip.handle_input(event);
		}	
		// Make the screen white	
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	//	apply_surface(0, 0, myShip.image, screen);
		myShip.move();
		myShip.show(screen);
		// Apply player and generated prjoectiles

		// Apply enemy and generated projectiles

		if(SDL_Flip(screen) == -1)
		{
			return 0;
		}
		
		if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}
	SDL_Quit;
	return 0;
}


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
}
	// If the timer isn't running
