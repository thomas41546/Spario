#ifndef OBJ
#define OBJ
#include "../../lib/global.h"
#include "../../lib/t_filehandling/filehandling.h"
#include "../../lib/p_vector/vector.h"
#include <stdlib.h>

struct SSpriteMap{ //for mobs only
       int dead;
       int standLeft;
       int standRight;
       int skidLeft;
       int skidRight;
       int jumpLeft;
       int jumpRight;
       int walkLeft;
       int walkRight;
};


class Obj{
      public:
          Vector Pos;
          Vector LastPos;
          Vector Dim;
          Vector Velocity;
          Vector LastVelocity;
          
          
          SSpriteMap * SpriteMap;
          double LastSpriteChange;
          double AirHeight;
          
          double VarA;
          double VarB;
          double VarC;
          
          
          int Sprite; //animation reference number
          int SpriteIt; //image
          double LastSpriteIt; //ms
          
          
          int Type;
          
          Vector Spawn;
          Vector Target;

          Vector MapBlock;
          int Id;
      
          Obj();
          Obj(Vector, Vector, Vector,Vector, int,int);
          void Init(Vector, Vector, Vector,Vector, int,int); 
          void AllocSpriteMap();
          void DeAllocSpriteMap();
          void ChangeSprite(int);
};



#endif
