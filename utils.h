//Header file for utility functions


#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "Ship.h"
#include <string>
#include <vector>

// May need to be moved to main, will need three ints and surface for function
SDL_Surface* init(int width, int height, int bpp, SDL_Surface *screen);

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL);

SDL_Surface *load_image(std::string filename);

int handle_collisions(Ship* playerShip, std::vector<Ship*> enemyShips);

bool check_collision(SDL_Rect A, SDL_Rect B);

// TODO Should function be general purpose or load all files at once?
bool load_files();

#endif
