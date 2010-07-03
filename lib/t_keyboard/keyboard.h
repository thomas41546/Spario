#ifndef KEYBOARD
#define KEYBOARD
#include "../../lib/global.h"
class Keyboard{
public:
  bool Up;
  bool Down;
  bool Left;
  bool Right;
  bool Space;
  bool r,p,s;
  
  bool Quit;    
   
  Keyboard();
  void Poll();
  void Clear();
};
#endif
