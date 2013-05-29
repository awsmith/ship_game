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
		void handle_input(SDL_Event &event);

		// Move ship and hitbox
		void move();

		// Apply ship to a surface
		void show(SDL_Surface *destination);

		// Return coordinates
		const SDL_Rect get_xy();

		// Return hitbox
		const SDL_Rect get_hitBox();

		// Return health remaining
		const int get_hp();

		// Return ship surface
		SDL_Surface *get_image();

		// Surface image for ship	
		SDL_Surface* image;

	private:
		// Coordinates
		SDL_Rect offset[2];

		// Hitbox
		SDL_Rect hitBox;

		// Orientation of ship
		int status;

		// Velocity
		int v_x;
		int v_y;
		
		// Image file
		std::string filename;

		// Current image frame
		int frame;

		// Health points of ship
		int hp;

};

#endif
