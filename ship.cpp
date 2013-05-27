// Implementation file for ship.h
// Has not been tested 13/05/11

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

        offset[1].x = 0;
	offset[1].y = 40;
	offset[1].w = 37;
	offset[1].h = 32;

	status = 0;
	v_x = 0;
	v_y = 0;
	filename = "ship.png";
	image = NULL;
	frame = 0;
	hp = 1;
	hitBox.x = 0;
	hitBox.y = 0;
	hitBox.w = 40;
	hitBox.h = 35;
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
{
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: v_x += 20; break;
			case SDLK_DOWN: v_x -= 20; break;
			case SDLK_LEFT: v_y -= 20; break;
			case SDLK_RIGHT: v_y += 20; break;
		}
	}

	else if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: v_x -= 20; break;
			case SDLK_DOWN: v_x += 20; break;
			case SDLK_LEFT: v_y += 20; break;
			case SDLK_RIGHT: v_y -= 20; break;
		}
	}
}

// Move ship and hitbox
// TODO: check screen edges, check collisions(?)
void ship::move()
{
//	offset.x += v_x;
	hitBox.x += v_x;

//	offset.y += v_y;
	hitBox.y += v_y;

	if(false)
	{
//		offset.x -= v_x;
		hitBox.x -= v_x;
	}

	if(false) //  wat, both if statements will execute
	{
//		offset.y -= v_y;
		hitBox.y -= v_y;
	}
}

// Apply ship to a surface
void ship::show(SDL_Surface *destination)
{
	apply_surface(hitBox.x, hitBox.y, image, destination, &offset[frame]);

}

// Return coordinates
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
