//Utility functions used in ship game
#include <iostream>

#include "utils.h"

//Functions
//TODO: Comment functions

// Initialize SDL stuff and the screen
SDL_Surface* init(int width, int height, int bpp, SDL_Surface *screen)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return NULL;
	}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);

	if(screen == NULL)
	{
		return NULL;
	}

	SDL_WM_SetCaption("Game", NULL);

	return screen;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, clip, destination, &offset);
}

void handle_collisions(std::vector<Ship> ships)
{
	// Number of ships to check for collisions
	int numShips = ships.size();
	// Number of collisions to check against for current ship
	int numProjs = 0;
	// Number of hits the current ship has taken
	int hits;
	// Coordinates to check collision of current objects
	SDL_Rect shipHitBox, projHitBox;

	for(int x = 0; x < numShips; x++)
	{
		// Store coordinates for current ship

		// Set numProjs to size of projectile vector for ships[x]
		for(int y = 0; y < numProjs; y++)
		{
			// TODO: Create projectile class, set to current projectile coords

			// Check collision of ships[x] and projecticles
			if(check_collision(shipHitBox, projHitBox))
			{
				// Increment hits for each collision detected
				hits++;
			}
		}

		// If ship was hit
		if(hits > 0)
		{
			// Deal damage to ship based on number of hits
			// TODO: Create take damage function for ship class
			hits = 0;
		}

		// Check health status of current ship
	}

}

SDL_Surface *load_image(std::string filename)
{
	//Temporary storage for the image that's loaded
	SDL_Surface *loadedImage = NULL;

	//Optimized image that will be used
	SDL_Surface *optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());

	//If nothing went wrong in loading the image
	if(loadedImage != NULL)
	{
	//Create an optimized image
	optimizedImage = SDL_DisplayFormat(loadedImage);

	//Free the old image
	SDL_FreeSurface(loadedImage);
	}

	//If the image was optimized without error
	if(optimizedImage != NULL)
	{
	//Map the color key
	Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0xFF, 0xFF);

	//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
	SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
	}

	//Return the optimized image
	return optimizedImage;
}

bool check_collision(SDL_Rect A, SDL_Rect B)
{
  if(A.y + A.h <= B.y)
  {
    return false;
  }

  if(A.y >= B.y + B.h)
  {
    return false;
  }

  if(A.x + A.w <= B.x)
  {
    return false;
  }

  if(A.x >= B.x + B.w)
  {
    return false;
  }

  return true;
}
