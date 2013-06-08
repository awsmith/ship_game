#ifndef Projectile_H_INCLUDED
#define Projectile_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

class Projectile
{
  public:
    Projectile();
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

    SDL_Surface *image();

  private:
    int damage;
    int v_x;
    int v_y;
    int frame;
    SDL_Rect offset[2];
    SDL_Rect hitbox;
    std::string filename;
};

#endif
