#ifndef CAMERACONTROLLER
#define CAMERACONTROLLER
#include "../../lib/global.h"
#include "../../lib/p_vector/vector.h"
#include "../../lib/t_rect/rect.h"

class CameraController{
      public:
          Vector PlayerPos;
          Vector CurrentPos;
          Vector TargetPos;
          
          Rect Boundary;
          Rect Screen;

          CameraController();
          void SetCamera(Vector );
};

#endif 
