#ifndef MAP
#define MAP
#include "../../lib/global.h"
#include "../../lib/t_filehandling/filehandling.h"
#include "../../lib/p_vector/vector.h"
#include <stdlib.h>

class Map{
      private:
          unsigned int *data;
          int W,H;
          
      public:
             Map();
             void load(char *, char * );
             void writeFlag(Vector Loc,int bit,bool state); //15-0
             bool readFlag(Vector Loc,int bit); //15-0
             int read(Vector Loc);
             int getWidth();
             int getHeight();
};


#endif
