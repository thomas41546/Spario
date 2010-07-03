#ifndef PLAYERCONTROLLER
#define PLAYERCONTROLLER
#include "../../lib/global.h"
#include "../../lib/p_vector/vector.h"
#include "../../lib/t_obj/obj.h"
#include "../../lib/t_gameobjcontroller/gameobjcontroller.h"
#include "../../lib/t_mapobjtrans/mapobjtrans.h"
#include "../../lib/t_keyboard/keyboard.h"
class PlayerController{
      
      private:
           GameObjectController * GameObjectControllerPtr; 
           MapObjGameTranslator * pMapObjTrans;
           Keyboard * pKeyboard;
           
           Obj * PlayerPtr;
           
           double jumpStartPosY;
           
           
      public:
             
           PlayerController();
           PlayerController(Keyboard * p_gkeyb, GameObjectController * p_goc,MapObjGameTranslator * p_mot);
           void KeyboardUpdate();
           Obj * PlayerPt();
           Vector PlayerPos();
           Vector PlayerVelocity();
           Vector PlayerLastVelocity();
           
};
#endif 
