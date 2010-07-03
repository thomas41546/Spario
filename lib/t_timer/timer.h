#ifndef TIMER
#define TIMER
#include "../../lib/global.h"
#include <SDL/SDL.h>
class Timer {
  private:
      double start,stop;
  public:
      Timer();
      void startTimer( ) ;
      void stopTimer( );
      double getElapsedTime();
      double pollTimer( );
};

#endif 
