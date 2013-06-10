all:
	g++ game.cpp utils.cpp Ship.cpp Projectile.cpp timer.cpp -lSDL -lSDL_image -lSDL_mixer -o ship 

