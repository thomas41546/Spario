#include "timer.h"
    Timer::Timer(){
        Timer::start =  Timer::stop =  0.0;
    }
    void Timer::startTimer( ) {
	     Timer::start = (double)SDL_GetTicks();
    }
    void Timer::stopTimer( ) {
	     Timer::stop = (double)SDL_GetTicks(); 
    }
    double Timer::getElapsedTime() {
        return (double) (Timer::stop - Timer::start);
    }
    double Timer::pollTimer() {//ms
    	return (double)SDL_GetTicks();
    }
