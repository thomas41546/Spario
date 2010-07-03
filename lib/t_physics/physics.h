#ifndef PHYSICS
#define PHYSICS
#include "../../lib/global.h"
#include "../../lib/t_timer/timer.h"
#include "../../lib/p_vector/vector.h"
#include "../../lib/t_rect/rect.h"
#include "../../lib/t_gameobjcontroller/gameobjcontroller.h"
#include "../../lib/t_playercontroller/playercontroller.h"
#include "../../lib/sdl_collide/SDL_collide.h"
class CollisionObj{
      public:
          Obj *ref; //relative to this object
             
          Obj *left;
          Obj *right;
          Obj *up;
          Obj *down;
          
          CollisionObj();
          CollisionObj(Obj *reference);
          bool CollisionTrue();
          bool Vertical();
          bool Horizontal();
};

class PhysicsEngine{
      public:
          GameObjectController * GameObjectControllerPtr;
          PlayerController * pPlayer;
          Display * pDisplay;  
          Timer * pTimer;
          PhysicsEngine(Display *,GameObjectController *,PlayerController *,Timer *);
          void ObjectSpriteIteration(Obj *);
          void Collision_HandlingVerticalCase(Obj *, CollisionObj * ,CollisionObj * , Vector * , Vector * );
          void Collision_HandlingHorizontalCase(Obj *, CollisionObj * ,CollisionObj * , Vector * , Vector * );
          void ApplyGravity();
          void ApplyVelocity();
          void ApplyAI(Obj *);
          double FrictionHandler(Obj *,Vector *,Obj *);
          void ChangeObjSprite(Obj * , int );
          void Collision_Handling(Obj * );
          CollisionObj InvasiveCollisionCheck(Obj *, Vector );
          int AirHeight(Obj *, Vector );
          int DirtyAirHeight(Obj *,Vector);
};
#endif 
