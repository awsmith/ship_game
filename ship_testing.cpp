#include <iostream>
#include "utils.h"
#include "Ship.h"

int main()
{
  SDL_Surface *screen = NULL;
  screen = init(640, 480, 32, screen);
  Ship tempShip;
  std::cout << "tempShip coords:\nX: " << tempShip.get_coords().x << "\nY: " << tempShip.get_coords().y << '\n';
  return 0;
}
