#include "playercontroller.h"
#define PC PlayerController
           PC::PlayerController(){}
           
           PC::PlayerController(Keyboard * p_gkeyb, GameObjectController * p_goc, MapObjGameTranslator *p_mot){
                 PC::pKeyboard = p_gkeyb;
                 PC::GameObjectControllerPtr = p_goc;
                 PC::pMapObjTrans = p_mot;
                 if(PC::PlayerPtr == NULL){
                     PC::pMapObjTrans->ObjectMapper(PLAYEROBJ,Vector(4,35)); //Add Player Object
                     for(std::list<Obj>::iterator objIterator = PC::GameObjectControllerPtr->ObjectIteratorBegin();  //Get Player Object Pointer
                         objIterator !=  PC::GameObjectControllerPtr->ObjectIteratorEnd(); 
                         objIterator++){
                            if(objIterator->Type == PLAYER){  
                                  PC::PlayerPtr = &(*objIterator);
                                  return;
                            }
                     } 
                }
           }
           
           void PC::KeyboardUpdate(){ 
                PC::pKeyboard->Poll();
                if(PC::pKeyboard->Up  && PC::PlayerPtr->Velocity.y > -MAX_VELOCITY){
                                          
                     if(PC::PlayerPtr->Velocity.y < JUMPTHRESHOLD && PC::PlayerPtr->Velocity.y > -JUMPTHRESHOLD && PC::PlayerPtr->AirHeight == 0){
                          PC::jumpStartPosY = PC::PlayerPtr->Pos.y;
                          PC::PlayerPtr->Velocity.y -= JUMPSTARTVELOCITY*MOVEMENT_MULTIPLIER;
                     }
                     else if(PC::jumpStartPosY - PC::PlayerPtr->Pos.y <=  MAX_JUMP && PC::PlayerPtr->Velocity.y <= 0 && PC::jumpStartPosY != JUMPCODE){
                            PC::PlayerPtr->Velocity.y -= 4*MOVEMENT_MULTIPLIER;
                     }
                     else{
                          PC::jumpStartPosY = JUMPCODE;
                     }
                     
                 }
                 else if(PC::pKeyboard->Left && (int)abs((int)PC::PlayerPtr->Velocity.x ) <= BLOCK_SIZE/2 && PC::PlayerPtr->Velocity.x > -MAX_VELOCITY){
                     
                     if(PC::PlayerPtr->AirHeight == 0){
                      
                         if(PC::PlayerPtr->Velocity.x > 4*MOVEMENT_MULTIPLIER){ //skid
                             PC::PlayerPtr->Velocity.x -= 4*MOVEMENT_MULTIPLIER;
                         }                                          
                         else if(PC::PlayerPtr->Velocity.x < -2*MOVEMENT_MULTIPLIER){
                               PC::PlayerPtr->Velocity.x *= 1.6*MOVEMENT_MULTIPLIER;                              
                         }
                         else{
                              PC::PlayerPtr->Velocity.x -= 2*MOVEMENT_MULTIPLIER;  
                         }
                     }
                     else{                          
                         if(PC::PlayerPtr->Velocity.x < -2*MOVEMENT_MULTIPLIER){
                               PC::PlayerPtr->Velocity.x *= 1.2*MOVEMENT_MULTIPLIER;                              
                         }
                         else{
                              PC::PlayerPtr->Velocity.x -= 1*MOVEMENT_MULTIPLIER;  
                         }
                     }
                 }
                 else if(PC::pKeyboard->Right && (int)abs((int)PC::PlayerPtr->Velocity.x) <= BLOCK_SIZE/2 && PC::PlayerPtr->Velocity.x < MAX_VELOCITY){
                   if(PC::PlayerPtr->AirHeight == 0){
                         if(PC::PlayerPtr->Velocity.x < -4*MOVEMENT_MULTIPLIER){ //skid
                             PC::PlayerPtr->Velocity.x += 4*MOVEMENT_MULTIPLIER;
                         }        
                         if(PC::PlayerPtr->Velocity.x > 2*MOVEMENT_MULTIPLIER){
                               PC::PlayerPtr->Velocity.x *= 1.6*MOVEMENT_MULTIPLIER;                              
                         }
                         else{
                              PC::PlayerPtr->Velocity.x += 2*MOVEMENT_MULTIPLIER;  
                         }
                     }
                     else{                          
                         if(PC::PlayerPtr->Velocity.x > 2*MOVEMENT_MULTIPLIER){
                               PC::PlayerPtr->Velocity.x *= 1.2*MOVEMENT_MULTIPLIER;                              
                         }
                         else{
                              PC::PlayerPtr->Velocity.x += 1*MOVEMENT_MULTIPLIER;  
                         }
                     }
                     
                 }
           }
           Obj * PC::PlayerPt(){
               return PC::PlayerPtr;
           }    
           
           Vector PC::PlayerPos(){
                  return (PC::PlayerPtr->Pos);
           }
           Vector PC::PlayerVelocity(){
                  return (PC::PlayerPtr->Velocity);
           }
           Vector PC::PlayerLastVelocity(){
                  return (PC::PlayerPtr->LastVelocity);
           }
