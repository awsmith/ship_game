#include <iostream>
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "Ship.h"
#include "SDL/SDL_mixer.h"

class Level
{
	public:
		// TODO: Add file I/O?
		void set_level();
		// Push the player to the ships vector
		void add_player(Ship* player);
		// Return the background for the level to apply to the screen
		std::string get_background();	
		// Return the music for the level to set
		Mix_Music* get_music();
	private:
		// Filename for the level background
		std::string background;
		// Vector of ships for the level
		std::vector<Ship*> ships;
		// Music for the level
		Mix_Music *music;		
};
