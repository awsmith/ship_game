// Header file for the timer class
#include "SDL/SDL.h"

#ifndef TIMER_H
#define TIMER_H

class Timer
{
	public:
		// Default constructor
		Timer();

		// Clock functions
		void start();
		void stop();
		void pause();
		void unpause();
	
		// Check the timer's time	
		int get_ticks();

		// Check the status of the timer
		bool is_started();
		bool is_paused();

	private:
		// The ticks stored when the timer is started
		int startTicks;
		
		// The ticks stored when the timer is paused
		int pausedTicks;
		
		// The timer status
		bool paused;
		bool started;
};

#endif
