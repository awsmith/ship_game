#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED


class Projectile
{
	public:
		Projectile(SDL_Rect origin);
		~Projectile();

		//Move projectile
		void move();

		//Apply projectile to a surface
		void show(SDL_Surface *destination);

		//Return coordinates
		const SDL_Rect get_coords();

		//Return hitbox
		const SDL_Rect get_hitbox();

		//Return damage amount
		const int get_damage();

		//Return Projectile surface
		SDL_Surface *get_image();

		SDL_Surface *image;
		bool get_destroy();

	private:
		bool destroy;
		int damage;
		int v_x;
		int v_y;
		int frame;
		int status;
		SDL_Rect offset[2];
		SDL_Rect hitBox;
		std::string filename;
};

#endif
