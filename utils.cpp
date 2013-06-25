//Utility functions used in ship game
#include <iostream>
#include "Ship.h"
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

int handle_collisions(Ship* currentShip, std::vector<Ship*> ships)
{
	SDL_Rect currentShipCoords = (*currentShip).get_coords();
	SDL_Rect originalShipCoords = (*currentShip).get_coords();
        currentShipCoords.x += (*currentShip).get_xVel();
        currentShipCoords.y += (*currentShip).get_yVel();

        SDL_Rect enemyCoords;
        SDL_Rect projectileCoords;
	int collisions = 0;
	std::vector<Ship*>::iterator shipItr = ships.begin();
        std::list<Projectile*> currentEnemyProjectiles;
        std::list<Projectile*>::iterator projectileItr;

	for(shipItr = ships.begin(); shipItr < ships.end(); shipItr++)
	{
		enemyCoords = (*shipItr)->get_coords();

                if((originalShipCoords.x == enemyCoords.x) && (originalShipCoords.y == enemyCoords.y))
                {
                  continue;
                }

		if(check_collision(currentShipCoords, enemyCoords) == true)
		{
                  //TODO: change amount of damage taken by impact with a ship
                  collisions++;
                  (*currentShip).take_damage(0);
		}

                //Set iterator to current enemy ship projectile list
                currentEnemyProjectiles = (*shipItr)->get_projectiles();
                projectileItr = currentEnemyProjectiles.begin();
               while(projectileItr != currentEnemyProjectiles.end())
                {
                  projectileCoords = (*projectileItr)->get_coords();
                  if(check_collision(currentShipCoords, projectileCoords) == true)
                  {
                    collisions++;
                    (*currentShip).take_damage((*projectileItr)->get_damage());
                    (*projectileItr)->set_destroy(true);

                  }
                  projectileItr++;
                }
	}
	return collisions;
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
