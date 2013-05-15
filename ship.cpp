// Implementation file for ship.h
// Has not been tested 13/05/11

#include "ship.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// Constructor
ship::ship()
{
        offset.x = 0;
	offset.y = 0;
	status = 0;
	v_x = 0;
	v_y = 0;
	file = "ship.png";
	frame = 0;
	hp = 1;
	hitBox.x = 0;
	hitBox.y = 0;
	hitBox.w = 40;
	hitBox.h = 35;
}

// Controls
void ship::handle_input()
{
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysm.sym)
		{
			case SDLK_UP: v_x += 20; break;
			case SDLK_DOWN: v_x -= 20; break;
			case SDLK_LEFT: v_y -= 20; break;
			case SDLK_RIGHT: v_y += 20; break;
		}
	}

	else if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysm.sym)
		{
			case SDLK_UP: v_x -= 20; break;
			case SDLK_DOWN: v_x += 20; break;
			case SDLK_LEFT: v_y += 20; break;
			case SDLK_RIGHT: v_y -= 20; break;
		}
	}
}

// Move ship and hitbox
// TODO: check screen edges, move hitBox, check collisions(?)
void ship::move()
{
  offset.x += v_x;

  if(false)
  {
    offset.x -= v_x;
  }

  offset.y += v_y;

  if(false)
  {
    offset.y -= v_y;
  }
}

// Apply ship to a surface
void ship::show()
{
// PLACEHOLDER
}

// Return coordinates
const SDL_Rect ship::get_xy()
{
// PLACEHOLDER
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
