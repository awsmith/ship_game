#include <iostream>
#include "Ship.h"

// Constructor
Ship::Ship(int x , int y)
{
	// First frame of ship animation
        offset[0].x = 0;
	offset[0].y = 0;
	offset[0].w = 37;
	offset[0].h = 32;
	// Second frame of ship animation
        offset[1].x = 40;
	offset[1].y = 0;
	offset[1].w = 37;
	offset[1].h = 32;
	// Coordinates for ship
	hitBox.x = x;
	hitBox.y = y;
	hitBox.w = 37;
	hitBox.h = 32;

	status = 0;
	v_x = 0;
	v_y = 0;
	filename = "ship.png";
	image = load_image(filename);
	frame = 1;
	hp = 1;
	projDelay = 0;
}

// Destructor
Ship::~Ship()
{
	// All other variables handled once Ship is out of scope?
	SDL_FreeSurface(image);
}

// Controls
void Ship::handle_input(SDL_Event &event)
{
	// If a key is pressed
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			// Create projectile
			case SDLK_SPACE: projectiles.push_back(new Projectile(hitBox)); break;
			// Increase velocity for desired direction
			case SDLK_UP: v_y -= hitBox.h / 4; break;
			case SDLK_DOWN: v_y += hitBox.h / 4; break;
			case SDLK_LEFT: v_x -= hitBox.w / 4; break;
			case SDLK_RIGHT: v_x += hitBox.w / 4; break;
		}
	}
	// If a key is released
	else if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			// Decrease velocity for desired direction
			case SDLK_UP: v_y += hitBox.h / 4; break;
			case SDLK_DOWN: v_y -= hitBox.h / 4; break;
			case SDLK_LEFT: v_x += hitBox.w / 4; break;
			case SDLK_RIGHT: v_x -= hitBox.w / 4; break;
		}
	}
}

// Move Ship and hitbox
void Ship::move()
{
	// Update ships coordinates based on current x, y velocities
	hitBox.x += v_x;
	hitBox.y += v_y;

	// Keep ship within screen width
	if((hitBox.x < 0) || ((hitBox.x + hitBox.w) > 640))
	{
		hitBox.x -= v_x;
	}

	// Keep ship within screen height
	if((hitBox.y < 0) || ((hitBox.y + hitBox.h) > 480))
	{
		hitBox.y -= v_y;
	}
}

void Ship::move_projectiles()
{
        std::list<Projectile*>::iterator itr;
	for(itr = projectiles.begin(); itr != projectiles.end();)
	{
		// Move current Projectile
		(*itr)->move();

		// Check if projectile is still alive
		//if(((*itr)->get_destroy() == true) || handle_collisions((*itr)->get_coords(), ships))
		if((*itr)->get_destroy() == true)
		{
			//TODO: Deal damage to ships hit
			// Clean up list and memory as needed
			delete *itr;
			itr = projectiles.erase(itr);
		}

		// Increment iterator if last projectile is still alive
		else
		{
			itr++;
		}
        }
}

// Apply Ship to a surface
void Ship::show(SDL_Surface *destination)
{
	// Apply ship to the screen
	apply_surface(hitBox.x, hitBox.y, image, destination, &offset[frame]);
	// Increment the frame counter
	frame++;
	// If the frame counter is at the last frame reset it
	if(frame >= 2)
	{
		frame = 0;
	}

	// Show projectiles
	std::list<Projectile*>::iterator itr;
	for(itr = projectiles.begin(); itr != projectiles.end(); ++itr)
	{
		// Apply projectiles to the screen
		(*itr)->show(destination);
	}
}

// Return width, height and x,y coordinates of the ship
const SDL_Rect Ship::get_coords()
{
	return hitBox;
}

// Return hitbox
const SDL_Rect Ship::get_hitBox()
{
	return hitBox;
}

// Return health remaining
const int Ship::get_hp()
{
	return hp;
}

//Return the ship's list of projectiles
std::list<Projectile*> Ship::get_projectiles()
{
  return projectiles;
}

// Reduce hp of ship
void Ship::take_damage(int damageDealt)
{
	hp -= damageDealt;
}

const int Ship::get_xVel()
{
  return v_x;
}

const int Ship::get_yVel()
{
  return v_y;
}

// Handle NPC ship actions
void Ship::ai()
{

	// Update ships coordinates based on current x, y velocities
	hitBox.x += v_x;
	hitBox.y += v_y;
	// Increment delay counter for NPC attack
	projDelay++;	

	if(projDelay == 40)
	{
		// Create new projectile
		projectiles.push_back(new Projectile(hitBox));
		// Reset counter
		projDelay = 0;	
	}
	// Keep ship within screen width
	if((hitBox.x < 0) || ((hitBox.x + hitBox.w) > 640))
	{
		// Remove hitbox update to keep NPC on screen
		hitBox.x -= v_x;
		// Reverse velocity to stop ship from going in x direction 
		v_x = -v_x;
	}

	// Keep ship within screen height
	if((hitBox.y < 0))
	{
		// Reverse y velocity to keep ship on screen
		v_y = -v_y;
	}
	
	else if((hitBox.y + hitBox.h) > 480)
	{
		// TODO: Remove NPC ship from vector
	}
}
