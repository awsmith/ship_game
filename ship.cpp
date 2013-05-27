// Implementation file for ship.h
// Has not been tested 13/05/11
#include <iostream>
#include "ship.h"
#include "utils.h"
// By including utils.h including SDL.h and SDL_image.h may not be needed, will comment out for now
//#include "SDL/SDL.h"
//#include "SDL/SDL_image.h"

// Constructor
ship::ship()
{

        offset[0].x = 0;
	offset[0].y = 0;
	offset[0].w = 37;
	offset[0].h = 32;

        offset[1].x = 40;
	offset[1].y = 0;
	offset[1].w = 37;
	offset[1].h = 32;

	status = 0;
	v_x = 0;
	v_y = 0;
	filename = "ship.png";
	image = load_image(filename);
	frame = 1;
	hp = 1;
	hitBox.x = 0;
	hitBox.y = 0;
	hitBox.w = 37;
	hitBox.h = 32;
}

// Destructor
ship::~ship()
{
	// All other variables handled once ship is out of scope?
	SDL_FreeSurface(image);
}

// Controls
void ship::handle_input(SDL_Event &event)
{
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: v_y -= hitBox.h / 4; break;
			case SDLK_DOWN: v_y += hitBox.h / 4; break;
			case SDLK_LEFT: v_x -= hitBox.w / 4; break;
			case SDLK_RIGHT: v_x += hitBox.w / 4; break;
		}
	}

	else if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: v_y += hitBox.h / 4; break;
			case SDLK_DOWN: v_y -= hitBox.h / 4; break;
			case SDLK_LEFT: v_x += hitBox.w / 4; break;
			case SDLK_RIGHT: v_x -= hitBox.w / 4; break;
		}
	}
}

// Move ship and hitbox
// TODO:check collisions(?)
void ship::move()
{
	hitBox.x += v_x;

	hitBox.y += v_y;

	if((hitBox.x < 0) || ((hitBox.x + hitBox.w) > 640))
	{
		hitBox.x -= v_x;
	}

	if((hitBox.y < 0) || ((hitBox.y + hitBox.h) > 480))
	{
		hitBox.y -= v_y;
	}
}

// Apply ship to a surface
void ship::show(SDL_Surface *destination)
{
	apply_surface(hitBox.x, hitBox.y, image, destination, &offset[frame]);
	frame++;
	if(frame >= 2)
	{
		frame = 0;
	}
}

const SDL_Rect ship::get_xy()
{
	return hitBox;
}

// Return hitbox
const SDL_Rect ship::get_hitBox()
{
	return hitBox;
}

// Return health remaining
const int ship::get_hp()
{
	return hp;
}
