#include "mapobjtrans.h"
#define MOGT MapObjGameTranslator
        MOGT::MapObjGameTranslator(Display * p_display,Map * p_map, GameObjectController * p_goc, CameraController * p_cc){
             MOGT::pDisplay = p_display;
             MOGT::pMap = p_map;
             MOGT::GameObjectControllerPtr = p_goc;
             MOGT::CameraControllerPtr = p_cc;
            
        }
          
        void MOGT::MapObjTranslate(){
             Vector blk_Start = MOGT::CameraControllerPtr->Boundary.Pos/BLOCK_SIZE;
             Vector blk_End = blk_Start + MOGT::CameraControllerPtr->Boundary.Dim/BLOCK_SIZE; 
                    blk_End.apply_ceil();
                    
             for(int y= (int)blk_Start.y; y < (int)blk_End.y; y++){
                 for(int x=(int)blk_Start.x; x < (int)blk_End.x; x++){
                          if(x < MOGT::pMap->getWidth() && y < MOGT::pMap->getHeight() && x >= 0 && y >= 0){
                               if(!MOGT::pMap->readFlag(Vector(x,y),MARKER) && MOGT::pMap->read(Vector(x,y)) != 0){//remove !=0 condition in alpha stages
                                     int tmp = 0;
                                     if(MOGT::GameObjectControllerPtr->pDisplay->GetAnimationSurface(MOGT::pMap->read(Vector(x,y)),&tmp) != NULL){
                                          MOGT::ObjectMapper(MAPOBJ,Vector(x,y));
                                     }
                                     else{
                                          DebugMsg("MOGT::MapObjTranslate() Invalid Map Code");
                                     }
                               }
                          }
                 }
             }
        }
        void MOGT::ObjMapTranslate(){
             for(std::list<Obj>::iterator objIterator = MOGT::GameObjectControllerPtr->ObjectIteratorBegin(); objIterator !=  MOGT::GameObjectControllerPtr->ObjectIteratorEnd(); objIterator++){
                  if(!MOGT::CameraControllerPtr->Boundary.BlockInside(objIterator->Pos, (int)objIterator->Dim.x) &&  //if outside of boundary
                      !MOGT::CameraControllerPtr->Boundary.BlockInside(objIterator->MapBlock*BLOCK_SIZE, (int)objIterator->Dim.x) && objIterator->Type != PLAYER){  //and does not ori. from inside the boundary, not player
                          MOGT::pMap->writeFlag(objIterator->MapBlock,MARKER,false); //unmark obj
                          objIterator = MOGT::GameObjectControllerPtr->RemoveObject(objIterator); //remove obj from objects
                  }
            } 
        }
        
        void MOGT::ObjectMapper(int code,Vector spawnpos){
             Obj dummy;
             if(code == MAPOBJ){          
                 dummy.Pos = spawnpos*BLOCK_SIZE;
                 dummy.Velocity = Vector(0,0);
                 dummy.Dim = Vector(BLOCK_SIZE,BLOCK_SIZE); //Incorrect
                 dummy.MapBlock = spawnpos;
                 dummy.Id = MOGT::pMap->read(spawnpos);
                 dummy.Sprite = dummy.Id;
                 dummy.Type = STATIC;
                 
                 switch(dummy.Id){
                      case(OBJECT_JUMPER):
                             dummy.Type = OBJECT;
                             dummy.VarA = 0;
                             break;
                      case(OBJECT_QUESTION_MARK):
                             dummy.Type = OBJECT;
                             dummy.VarA = 0;
                             break;
                             
                      case(OBJ_PLATFORM_3):
                             dummy.Type = OBJECT;
                             dummy.VarA = 0;
                             dummy.Dim = Vector(48,17);
                             break;
                             
                      case(MOB_GOOMPA):
                            dummy.Type = MOB;
                            dummy.VarA = 0;
                            dummy.VarB = 0;
                            dummy.AllocSpriteMap();
                            dummy.SpriteMap->dead = MOB_GOOMPA_DEAD;
                            dummy.SpriteMap->standLeft = MOB_GOOMPA;
                            dummy.SpriteMap->standRight = MOB_GOOMPA; 
                            dummy.SpriteMap->skidLeft = MOB_GOOMPA;
                            dummy.SpriteMap->skidRight = MOB_GOOMPA;
                            dummy.SpriteMap->jumpLeft = MOB_GOOMPA;
                            dummy.SpriteMap->jumpRight = MOB_GOOMPA;
                            dummy.SpriteMap->walkLeft = MOB_GOOMPA;
                            dummy.SpriteMap->walkRight = MOB_GOOMPA;
                            dummy.Sprite = MOB_GOOMPA;
                            break;
                      case(MOB_MAR):
                            dummy.Type = MOB;
                            dummy.VarA = 0;
                            dummy.VarB = 0;
                            dummy.AllocSpriteMap();
                            dummy.SpriteMap->dead = MOB_MAR_STANDL;
                            dummy.SpriteMap->standLeft = MOB_MAR_STANDL;
                            dummy.SpriteMap->standRight = MOB_MAR_STANDR; 
                            dummy.SpriteMap->skidLeft = MOB_MAR_STANDL;
                            dummy.SpriteMap->skidRight = MOB_MAR_STANDR;
                            dummy.SpriteMap->jumpLeft = MOB_MAR_STANDL;
                            dummy.SpriteMap->jumpRight = MOB_MAR_STANDR;
                            dummy.SpriteMap->walkLeft = MOB_MAR_WALKL;
                            dummy.SpriteMap->walkRight = MOB_MAR_WALKR;
                            dummy.Sprite = MOB_MAR;
                            break;
                      
                 }

             }
             else if(code == PLAYEROBJ){  
                     dummy.Pos = spawnpos*BLOCK_SIZE;
                     dummy.Velocity = Vector(0,0);
                     dummy.Dim = Vector(BLOCK_SIZE,BLOCK_SIZE);
                     dummy.MapBlock = Vector(-1,-1);
                     dummy.Id = 200;
                     dummy.Type = PLAYER;
                     
                     dummy.AllocSpriteMap();
                     dummy.SpriteMap->dead = 198;
                     dummy.SpriteMap->standLeft = 199;
                     dummy.SpriteMap->standRight = 200; 
                     dummy.SpriteMap->skidLeft = 205;
                     dummy.SpriteMap->skidRight = 206;
                     dummy.SpriteMap->jumpLeft = 203;
                     dummy.SpriteMap->jumpRight = 204;
                     dummy.SpriteMap->walkLeft = 202;
                     dummy.SpriteMap->walkRight = 201;
                     dummy.Sprite = dummy.SpriteMap->standRight;
             }
             /*
             int tmp = 0;
             SDL_Surface* spriteSDLSurface = MOGT::pDisplay->GetAnimationSurface(dummy.Sprite,&tmp);
             if(spriteSDLSurface != NULL)
                 dummy.Dim = Vector(spriteSDLSurface->w,spriteSDLSurface->h);
             */
             (*GameObjectControllerPtr).AddObject(dummy); // add to game object controller
             MOGT::pMap->writeFlag(spawnpos,MARKER,true); //Mark on map
        }
