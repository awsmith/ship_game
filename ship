// Header file for ship class

#ifndef SHIP_H
#define SHIP_H

class ship
{
  public:
		// Controls
		void handle_input();
		
		// Move ship and hitbox
		void move();
		
		// Apply ship to a surface
		void show();
		
		// Return coordinates
		const int get_x();
		const int get_y();
		
		// Return hitbox
		const SDL_Rect *get_hitBox();
		
		// Return health remaining
		const int get_hp();
		
	private:
		// Coordinates
		int x, y;
		
		// Hitbox
		SDL_Rect hitBox;
		
		// Orientation of ship
		int status;
		
		// Velocity
		int v;
		
		// Image file
		std::string;
		
		// Current image frame
		int frame;
		
		// Health points of ship
		int hp;
		
};

#endif
