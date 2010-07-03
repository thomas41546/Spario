#include "cameracontroller.h"
  CameraController::CameraController(){
        CameraController::Screen.Dim = Vector(SCREEN_W,SCREEN_H)*BLOCK_SIZE;
        CameraController::Boundary.Dim = Vector( (SCREEN_W+2*K_W),(SCREEN_H+2*K_H) )*BLOCK_SIZE;
                     
        CameraController::Screen.Pos =  Vector(0,0);
        CameraController::PlayerPos  = Vector(0,0);
        CameraController::CurrentPos = Vector(0,0);
        CameraController::TargetPos  = Vector(0,0);
        CameraController::Boundary.Pos = -Vector(K_W*BLOCK_SIZE,K_H*BLOCK_SIZE);

  }

  void CameraController::SetCamera(Vector ipos){
       CameraController::PlayerPos = ipos;
       CameraController::PlayerPos.x -= (SCREEN_W*BLOCK_SIZE/4);
       CameraController::PlayerPos.y -= (SCREEN_H*BLOCK_SIZE/4);
       CameraController::Screen.Pos = CameraController::PlayerPos;
       CameraController::Boundary.Pos = CameraController::PlayerPos - Vector(K_W*BLOCK_SIZE,K_H*BLOCK_SIZE);
  }
