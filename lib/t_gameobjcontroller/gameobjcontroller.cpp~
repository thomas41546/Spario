#include "gameobjcontroller.h"
#define GOC GameObjectController
          GOC::GameObjectController(Display * p_disp, CameraController * p_cc){
                 GOC::pDisplay = p_disp;
                 GOC::CameraControllerPtr = p_cc;
          }
          
          int GOC::CountObjects(){
              return GOC::objects.size();
          }
          
          void GOC::DebugObjects(){
              char buff[128];
              int count = 0;
              for(std::list<Obj>::iterator objIterator = GOC::objects.begin(); objIterator != GOC::objects.end(); objIterator++){
                   sprintf(buff,"%i:%i,%2.2f,%2.2f",count,objIterator->Id,objIterator->Pos.x,objIterator->Pos.y);
                   Debug(buff);
                   count++;
              }
          }
          
          void GOC::RenderObjects(){ //Seperate in Alpha
              for(std::list<Obj>::iterator objIterator = GOC::objects.begin(); objIterator != GOC::objects.end(); objIterator++){ 
                  int ox = (int)objIterator->Pos.x - (int)(GOC::CameraControllerPtr->Screen.Pos.x);
                  int oy = (int)objIterator->Pos.y - (int)(GOC::CameraControllerPtr->Screen.Pos.y); 
                  if(ox >= -objIterator->Dim.x  && oy >= -objIterator->Dim.y && ox < SCREEN_W*BLOCK_SIZE && oy < SCREEN_H*BLOCK_SIZE && objIterator->Id != 0){ //remove last Id!=0 cond
                        GOC::pDisplay->DrawAnimation(ox, oy,objIterator->Sprite,&objIterator->SpriteIt);
                  }
                       
              }
          }
          
          std::list<Obj>::iterator GOC::ObjectIteratorBegin(){
               return GOC::objects.begin();
          }
          
          std::list<Obj>::iterator GOC::ObjectIteratorEnd(){
               return GOC::objects.end();
          }
          
          void GOC::AddObject(Obj inobj){
               GOC::objects.push_front(inobj);
               GOC::objects.sort(objSorter);
          }
          
          std::list<Obj>::iterator GOC::RemoveObject(std::list<Obj>::iterator inobj){
               if(inobj->Type != PLAYER){
                  if(inobj->Type == MOB)
                        inobj->DeAllocSpriteMap();                  
                   return GOC::objects.erase(inobj);
               }
               return inobj;
          }
          
          void GOC::RemoveObjectP(Obj * inobja){ /*Todo: Doesn't work*/
              std::list<Obj>::iterator inobj;
	      bool foundObj = false;
              for(std::list<Obj>::iterator objIterator = GOC::objects.begin(); objIterator != GOC::objects.end(); objIterator++){
                  if(&(*objIterator) == inobja){
                         inobj = objIterator;
			 foundObj = true;
			 break; 
		
		}        
              }
              if(foundObj){         
                   if(inobj->Type != PLAYER){
                      if(inobj->Type == MOB)
                            inobj->DeAllocSpriteMap();                  
                      GOC::objects.erase(inobj);
                   }
              }
          }

