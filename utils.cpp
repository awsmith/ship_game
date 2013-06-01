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

void handle_collisions(std::vector<ship> ships)
{
	int numShips = ships.size();
	int numProjs = 0;	
	for(int x = 0; x < numShips; x++)
	{
		// Set numProjs to size of projectile vector for ships[x]	
		for(int y = 0; y < numProjs; y++)
		{
			// Check collision of ships[x] and projecticles
		}
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
