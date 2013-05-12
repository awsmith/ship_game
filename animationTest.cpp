// Using code from collision detection for animation test

// Headers
#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int SQUARE_HEIGHT = 19;
const int SQUARE_WIDTH = 15;

const int FRAMES_PER_SECOND = 20;

// Prototypes
bool init();
SDL_Surface *load_image(std::string filename);
bool load_files();
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL);
void clean_up();
bool check_collision(SDL_Rect A, SDL_Rect B);

// Surfaces
SDL_Surface *screen = NULL;
SDL_Surface *square = NULL;

// The wall
SDL_Rect wall;

// Events
SDL_Event event;

// Classes
class Timer
{
  public:
// Default constructor
  Timer();

	// The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	// Get the timer's time
	int get_ticks();

	// Checks the status of the timer
	bool is_started();
	bool is_paused();

	private:
	// The time when the timer startered
	int startTicks;

	// The ticks stored when the timer was paused
	int pausedTicks;

	// The timer status
	bool paused;
	bool started;
};

class Square
{
public:
	// Default constructor
	Square();
	// Takes the key presses and adjusts the square's velocity
	void handle_input();
	// Move the square
	void move();
	// Shows the square on the screen
	void show();

private:
	// The X and Y offsets of the square
	SDL_Rect box;
	// The velocity of the square
	int xVel, yVel;
	int frame;
};

int main(int argc, char *args[])
{
	Timer fps;
	Square mySquare;

	bool quit = false;

	if(init() == false)
	{
		return 1;
	}

	if(load_files() == false)
	{
		return 2;
	}

	// Set the wall
	wall.x = 300;
	wall.y = 40;
	wall.w = 40;
	wall.h = 400;

	while(quit == false)
	{
		// Start the frame timer
		fps.start();

		while(SDL_PollEvent(&event))
		{
			// Handle events for the square
			mySquare.handle_input();

			if(event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		mySquare.move();

		// Fill the screen white
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

		// Show the wall
		SDL_FillRect(screen, &wall, SDL_MapRGB(screen->format, 0x77, 0x77, 0x77));

		// Show the square on the screen
		mySquare.show();

		// Update the screen
		if(SDL_Flip(screen) == -1)
		{
			return 3;
		}

		// Cap the frame rate
		if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}
	clean_up();
	return 0;
}

bool init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if(screen == NULL)
	{
		return false;
	}
	SDL_WM_SetCaption("Collision", NULL);

	return true;
}

SDL_Surface *load_image(std::string filename)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		if(optimizedImage != NULL)
		{
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format,0, 0xFF, 0xFF));
		}
	}
	return optimizedImage;
}

bool load_files()
{
	square = load_image("ship2.png");

	if(square == NULL)
	{
		return false;
	}
	return true;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

void clean_up()
{
	SDL_FreeSurface(square);
	SDL_Quit();
}


bool check_collision(SDL_Rect A, SDL_Rect B)
{
	// The side of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	// Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	// If any of the sides from A are outside of B
	if(bottomA <= topB)
	{
		return false;
	}
	if(topA >= bottomB)
	{
		return false;
	}
	if(rightA <= leftB)
	{
		return false;
	}
	if(leftA >= rightB)
	{
		return false;
	}
	// If none of the side from A are outside B
	return true;
}


Square::Square()
{
	// Initialize the offsets
	box.x = 0;
	box.y = 0;
	box.w = 100;
	box.h = 50;
	// Initialize the velocity
	xVel = 0;
	yVel = 0;

	frame = 0;
}

void Square::handle_input()
{
	// If a key was pressed
	if(event.type == SDL_KEYDOWN)
	{
		// Adjust the velocity
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: yVel -= SQUARE_HEIGHT / 2; break;
			case SDLK_DOWN: yVel += SQUARE_HEIGHT / 2; break;
			case SDLK_LEFT: xVel -= SQUARE_WIDTH / 2; break;
			case SDLK_RIGHT: xVel += SQUARE_WIDTH / 2; break;
		}
	}

	// If a key was pressed
	else if(event.type == SDL_KEYUP)
	{
		// Adjust the velocity
		switch(event.key.keysym.sym)
		{
		case SDLK_UP: yVel += SQUARE_HEIGHT / 2; break;
		case SDLK_DOWN: yVel -= SQUARE_HEIGHT / 2; break;
		case SDLK_LEFT: xVel += SQUARE_WIDTH / 2; break;
		case SDLK_RIGHT: xVel -= SQUARE_WIDTH /2; break;
		}
	}
}

void Square::move()
{
	// Move the square left or right
	box.x += xVel;

	// If the square went too far too the left or right
	if( (box.x < 0) || (box.x + SQUARE_WIDTH > SCREEN_WIDTH) || (check_collision(box, wall)))
	{
		// Move back
		box.x -= xVel;
	}

	// Move the square up or down
	box.y += yVel;

	// If the square went too far up or down
	if( (box.y < 0) || (box.y + SQUARE_HEIGHT > SCREEN_HEIGHT) || (check_collision(box, wall)))
	{
		// Move back
		box.y -= yVel;
	}
}

void Square::show()
{
	SDL_Rect ship[3];
	ship[0].x = 0;
	ship[0].y = 0;
	ship[0].w = 38;
	ship[0].h = 35;

	ship[1].x = 40;
	ship[1].y = 0;
	ship[1].w = 38;
	ship[1].h = 35;

	ship[2].x = 100;
	ship[2].y = 0;
	ship[2].w = 40;
	ship[2].h = 35;

	// Show the square
	apply_surface(box.x, box.y, square, screen, &ship[frame]);
		frame++;
	if(frame >= 2)
	{
		frame = 0;
	}
}

Timer::Timer()
{
	// Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start()
{
	// Start the timer
	started = true;

	// Unpause the timer
	paused = false;

	// Get the current clock time
	startTicks =SDL_GetTicks();
}

void Timer::stop()
{
	// Stop the timer
	started = false;

	// Unpause the timer
	paused = false;

}

int Timer::get_ticks()
{
	// If the timer is running
	if(started == true)
	{
		// If the timer is paused
		if(paused == true)
		{
			// Return the number of ticks when the timer was paused
			return pausedTicks;
		}
		else
		{
			// Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}

	}
	// If the timer isn't running
	return 0;
}

void Timer::pause()
{
	// If the timer is running and isn't already paused
	if((started == true) && (paused == false))
	{
		// Pause the timer
		paused = true;

		// Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	// If the timer is paused
	if(paused == true)
	{
		// Unpaused the timer
		paused = false;

		// Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		// Reset the paused ticks
		pausedTicks = 0;
	}
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused;
}
