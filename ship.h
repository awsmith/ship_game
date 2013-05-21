// Header file for ship class
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

#ifndef SHIP_H
#define SHIP_H

class ship
{
  public:
  		// Constructor
		ship();
		
		// Destructor
		~ship();
		
		// Controls
		void handle_input();

		// Move ship and hitbox
		void move();

		// Apply ship to a surface
		/* If show calls apply_surface from utils.h there is no reference to screen outside of main
		   Pass screen as arugment to show()? */
		void show(SDL_Surface *destination);

		// Return coordinates
		const SDL_Rect get_xy();

		// Return hitbox
		const SDL_Rect get_hitBox();

		// Return health remaining
		const int get_hp();

	private:
		// Coordinates
		SDL_Rect offset;

		// Hitbox
		SDL_Rect hitBox;

		// Orientation of ship
		int status;

		// Velocity
		int v_x;
		int v_y;
	
		// Surface for class image
		/* If surfaces are local to their class there's no need to deal with the surface manually
		   Maybe? */
		SDL_Surface* image;
		
		// Image file
		std::string filename;

		// Current image frame
		int frame;

		// Health points of ship
		int hp;

};

#endif
