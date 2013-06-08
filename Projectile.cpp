#include "Projectile.h"
#include "utils.h"
#include <iostream>


Projectile::Projectile()
{
  offset[0].x = 0;
  offset[0].y = 0;
  offset[0].w = 37;
  offset[0].h = 32;

  offset[1].x = 40;
  offset[1].y = 0;
  offset[1].w = 37;
  offset[1].h = 32;

  status = 0;
  v_x = 0;
  v_y = 0;
  filename = "ship.png";
  image = load_image(filename);
  frame = 1;
  hitBox.x = 0;
  hitBox.y = 0;
  hitBox.w = 37;
  hitBox.h = 32;
}

Projectile::~Projectile()
{
  SDL_FreeSurface(image);
}

const int Projectile::get_damage()
{
  return damage;
}

const SDL_Rect Projectile::get_coords()
{
  return hitBox;
}

const SDL_Rect Projectile::get_hitbox()
{
  return hitBox;
}

void Projectile::show(SDL_Surface *destination)
{
  apply_surface(hitBox.x, hitBox.y, image, destination, &offset[frame]);
  frame++;
  if(frame >= 2)
  {
    frame = 0;
  }
}

void Projectile::move()
{
  hitBox.x += v_x;

  hitBox.y += v_y;

  if((hitBox.x < 0) || ((hitBox.x + hitBox.w) > 640))
  {
    hitBox.x -= v_x;
  }

  if((hitBox.y < 0) || ((hitBox.y + hitBox.h) > 480))
  {
    hitBox.y -= v_y;
  }
}

SDL_Surface* Projectile::get_image()
{
  return image;
}
