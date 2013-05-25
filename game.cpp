#include <iostream>
#include "utils.h"
#include "ship.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *screen = NULL;
SDL_Event event;

int main()
{
	SDL_Event event;	

	bool quit = false;

	screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screen);

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
		}	
		
		// Make the screen white	
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

		// Apply player and generated prjoectiles

		// Apply enemy and generated projectiles

		if(SDL_Flip(screen) == -1)
		{
			return 0;
		}
	}
	SDL_Quit;
	return 0;
}

