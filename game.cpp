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
	Ship *myShip = new Ship(100, 100, 0);
	Timer *fps = new Timer;

	// List to hold all ships
	std::vector<Ship*> ships;

	// Add player and enemy ship to list
	ships.push_back(myShip);

	// Add a bunch of ships for testing
	ships.push_back(new Ship(100, 200));
	ships.push_back(new Ship(100, 300));
	ships.push_back(new Ship(200, 200));
	ships.push_back(new Ship(400, 200));
	ships.push_back(new Ship(140, 350));
	ships.push_back(new Ship(390, 0));

	// While the user has not quit
	while(quit == false)
	{
		// If there are no NPC ships remaining on screen
		if(ships.size() == 1)
		{
			ships.push_back(new Ship(rand() % 600, 430 ));
			ships.push_back(new Ship(rand() % 600, 430 ));
		}

		// Start the fps timer
		fps->start();
		/// While there are events to handle
		while(SDL_PollEvent(&event))
		{
			// Handle input from user. Only accepts up, down, left and right keys currently.
			myShip->handle_input(event);
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
		std::vector<Ship*>::iterator itr = ships.begin();

		for(itr; itr != ships.end();)
		{
			(*itr)->move(ships);
			(*itr)->show(screen);
			
			// Check the health of the ship
			if((*itr)->get_hp() == 0)
			{
				// Clean up the ship vector if the ship's hp == 0
				delete *itr;
				itr = ships.erase(itr);
				
			}
			
			// Increment itr if the previous ship was not destroyed
			else
			{
				itr++;
			}
		}
		
		// Refresh screen
		if(SDL_Flip(screen) == -1)
		{
			return 0;
		}

		// Cap the frame rate if game is running too fast
		if(fps->get_ticks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps->get_ticks());
		}
		// If the player is dead
		if(myShip->get_hp() == 0)
		{
			std::cout << "You lose" << std::endl;
			quit = true;
		}
	}
	// Empty ships vector
	ships.clear();
	// Deallocate memory use for timer
	delete fps;
	SDL_Quit;
	return 0;
}

