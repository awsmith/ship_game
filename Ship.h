// Header file for ship class
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Projectile.h"
#include "utils.h"
#include <string>
#include <list>
#include <vector>
#ifndef SHIP_H
#define SHIP_H

class Ship
{
  public:
  		// Constructor
		Ship(int x = 0, int y = 0);

		// Destructor
		~Ship();

		// Controls
		void handle_input(SDL_Event &event);

		// Move ship and hitbox
		void move(std::vector<Ship*> ships);

		// Apply ship to a surface
		void show(SDL_Surface *destination);

		// Return coordinates
		const SDL_Rect get_coords();

		// Return hitbox
		const SDL_Rect get_hitBox();

		// Return health remaining
		const int get_hp();

		// Return ship surface
		SDL_Surface *get_image();

                // Return projectiles that were created by ship
                std::list<Projectile*> get_projectiles();

		// Surface image for ship
		SDL_Surface* image;

		// Reduces hp of ship
		void take_damage(int damageDealt);

                //TODO: comment
		const int get_xVel();

		const int get_yVel();

                void move_projectiles();

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

                // List of projectiles produced by ship
                std::list<Projectile*> projectiles;

};

#endif
