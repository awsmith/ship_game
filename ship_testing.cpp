#include <iostream>
#include "utils.h"
#include "Ship.h"

int main()
{
  SDL_Surface *screen = NULL;
  screen = init(640, 480, 32, screen);
  SDL_Event event;

  bool quit = false;

  std::vector<Ship*> shipList;
  std::vector<Ship*>::iterator it;

  while(quit == false)
  {
    while(SDL_PollEvent(&event))
    {
      std::cout << shipList.size() << std::endl;

      if(shipList.size() == 10)
      {
        while(shipList.size() > 0)
        {
          it = shipList.begin();
          delete * it;
          shipList.erase(it);
        }
      }
      else if(shipList.size() < 10)
      {
        shipList.push_back(new Ship());
      }

      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }

  return 0;
}
