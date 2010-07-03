#include "rect.h"

  Rect::Rect(){}
  
  Rect::Rect(Vector iPos, Vector iDim){
       Rect::Pos = iPos;
       Rect::Dim = iDim;
  }
  
  int Rect::BlockInside(Vector CheckPos, int width){
       if(CheckPos.x+width >= Rect::Pos.x && 
           CheckPos.y+width >= Rect::Pos.y &&
           CheckPos.x <= Rect::Pos.x + Rect::Dim.x &&
           CheckPos.y <= Rect::Pos.y + Rect::Dim.y)return 1;
           return 0;
  }
              
  int Rect::PtInside(Vector CheckPos){
       if(CheckPos.x >= Rect::Pos.x && 
          CheckPos.y >= Rect::Pos.y &&
          CheckPos.x <= Rect::Pos.x + Rect::Dim.x  &&
          CheckPos.y <= Rect::Pos.y + Rect::Dim.y)return 1;
       return 0;
  }
