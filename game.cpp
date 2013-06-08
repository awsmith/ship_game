#include <iostream>
#include "utils.h"
#include "Ship.h"
#include "timer.h"

// Game constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 30;

// Game surfaces
SDL_Surface *screen = NULL;

// Events
SDL_Event event;

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
	Ship myShip;
	Timer fps;
	SDL_Rect hitbox;
	// While the user has not quit
	while(quit == false)
	{
		// Start the fps timer
		fps.start();

		while(SDL_PollEvent(&event))
		{
			// Handle input from user. Only accepts up, down, left and right keys currently.
			myShip.handle_input(event);
			hitbox = myShip.get_coords();
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

