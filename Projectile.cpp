#include "Projectile.h"
#include "utils.h"
#include <iostream>

// Default constructor
Projectile::Projectile(SDL_Rect origin)
{
	destroy = false;
	// Clip first image for projectile animation
	offset[0].x = 0;
	offset[0].y = 0;
	offset[0].w = 37;
	offset[0].h = 32;
	// Clip second image for projectile animation
	offset[1].x = 40;
	offset[1].y = 0;
	offset[1].w = 37;
	offset[1].h = 32;

	status = 0;

	// Projectile velocities
	v_x = 0;
	v_y = -6;
	
	// Set image filename and load in
	filename = "ship.png";
	image = load_image(filename);
	frame = 1;

	// Projectile spawned at top center of ship
	hitBox.x = origin.x;
	hitBox.y = origin.y - origin.h; 
	hitBox.w = 37;
	hitBox.h = 32;
}

// Destructor
Projectile::~Projectile()
{
	SDL_FreeSurface(image);
}

// Return damage for projectile
const int Projectile::get_damage()
{
	return damage;
}

// Return the coordinates, width and height of the projectile
const SDL_Rect Projectile::get_coords()
{
	return hitBox;
}

const SDL_Rect Projectile::get_hitbox()
{
	return hitBox;
}

// Applies the projectile to the screen
void Projectile::show(SDL_Surface *destination)
{
	apply_surface(hitBox.x, hitBox.y, image, destination, &offset[frame]);

	// Increment the frame counter for animation
	frame++;
	
	// Check frame counter boundry
	if(frame >= 2)
	{
		// Reset the frame counter
		frame = 0;
	}
}

// Updates the x, y coordinates based on the projectile velocity
void Projectile::move()
{
	// Update x coordinate
	hitBox.x += v_x;
	// Update y coordinate
	hitBox.y += v_y;

	// Check if projectile goes out of x bounds
	if((hitBox.x < 0) || ((hitBox.x + hitBox.w) > 640))
	{
		destroy = true;
	}

	// Check if projectile goes out of y bounds
	if((hitBox.y < 0) || ((hitBox.y + hitBox.h) > 480))
	{
		destroy = true;
	}
}

// Returns the image for projectile
SDL_Surface* Projectile::get_image()
{
  return image;
}

bool Projectile::get_destroy()
{
	return destroy;
}
