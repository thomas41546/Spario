#ifndef GAMEOBJCONTROLLER
#define GAMEOBJCONTROLLER
#include <list>
#include "../../lib/global.h"
#include "../../lib/p_vector/vector.h"
#include "../../lib/t_rect/rect.h"
#include "../../lib/t_obj/obj.h"
#include "../../lib/t_display/display.h"
#include "../../lib/t_cameracontroller/cameracontroller.h"

bool objSorter(const Obj &f1, const Obj &f2);

class GameObjectController{
      public:
          CameraController * CameraControllerPtr;
          Display * pDisplay;
          std::list<Obj> objects;
          
          
          GameObjectController(Display *,CameraController * );
          int CountObjects();
          void RenderObjects();
          void DebugObjects();
          void AddObject(Obj );
          void RemoveObjectP(Obj * );
          std::list<Obj>::iterator RemoveObject(std::list<Obj>::iterator);
          std::list<Obj>::iterator ObjectIteratorBegin();
          std::list<Obj>::iterator ObjectIteratorEnd();
          
};
#endif 

