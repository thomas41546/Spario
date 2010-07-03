#ifndef RECTA
#define RECTA
#include "../../lib/p_vector/vector.h"
#include "../../lib/global.h"
class Rect{
      public:
          Vector Pos;
          Vector Dim;
          
          Rect();
          Rect(Vector, Vector);
          int BlockInside(Vector, int);
                      
          int PtInside(Vector);
};
#endif 
