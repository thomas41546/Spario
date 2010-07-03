#ifndef MAPBOJTRANS
#define MAPBOJTRANS
#include "../../lib/global.h"
#include "../../lib/p_vector/vector.h"
#include "../../lib/t_rect/rect.h"
#include "../../lib/t_obj/obj.h"
#include "../../lib/t_map/map.h"
#include "../../lib/t_gameobjcontroller/gameobjcontroller.h"
#include "../../lib/t_cameracontroller/cameracontroller.h"
class MapObjGameTranslator{ 
      public:
        GameObjectController * GameObjectControllerPtr;
        CameraController * CameraControllerPtr;       
        Map * pMap;
        Display * pDisplay;
             
        MapObjGameTranslator(Display *,Map *,GameObjectController * , CameraController * );
        void MapObjTranslate();
        void ObjMapTranslate();
        void ObjectMapper(int ,Vector );
};
#endif 
