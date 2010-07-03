#include "physics.h"
#define PE PhysicsEngine
#define CO CollisionObj

 CO::CollisionObj(){
  }
  
  CO::CollisionObj(Obj *reference){
       CO::ref = reference;
       CO::left = CO::right = CO::up = CO::down = NULL;
  }
  
  bool CO::CollisionTrue(){
       if(CO::left == NULL && CO::right == NULL && CO::up == NULL && CO::down == NULL)return false;
       return true;
  }
  bool CO::Vertical(){
       if(CO::up != NULL && CO::down != NULL)return true;
       return false;
  }
  bool CO::Horizontal(){
       if(CO::left != NULL && CO::right != NULL)return true;
       return false;
  }

 PE::PhysicsEngine(Display * p_disp,GameObjectController * p_goc,PlayerController * p_player,Timer * p_timer){
         PE::pDisplay = p_disp;                 
         PE::GameObjectControllerPtr = p_goc; 
         PE::pPlayer = p_player; 
         PE::pTimer = p_timer;
  }
  
  void PE::ApplyGravity(){
         for(std::list<Obj>::iterator objIterator = (*GameObjectControllerPtr).ObjectIteratorBegin(); 
             objIterator !=  (*GameObjectControllerPtr).ObjectIteratorEnd(); 
             objIterator++){
                if((objIterator->Type == PLAYER || objIterator->Type == MOB) && objIterator->Velocity.y < MAX_VELOCITY){  
                     objIterator->Velocity.y += GRAVITY*MOVEMENT_MULTIPLIER;
                }
               // if(objIterator->Velocity.y > MAX_VELOCITY)objIterator->Velocity.y = MAX_VELOCITY;
               // if(objIterator->Velocity.y < -MAX_VELOCITY)objIterator->Velocity.y = -MAX_VELOCITY;
         }  
  }
  void PE::ApplyAI(Obj * obby){
        if(abs((int)(PE::pPlayer->PlayerPos().x - obby->Pos.x)) > 2 && obby->Id == MOB_GOOMPA){
            if(PE::pPlayer->PlayerPos().x > obby->Pos.x){
                 obby->Velocity.x = 1*MOVEMENT_MULTIPLIER;                         
            }
            else{
                 obby->Velocity.x = -1*MOVEMENT_MULTIPLIER;
            }
        }
        if(abs((int)(PE::pPlayer->PlayerPos().x - obby->Pos.x)) > 2 && obby->Id == MOB_MAR){
            if(PE::pPlayer->PlayerPos().x > obby->Pos.x){
                 obby->Velocity.x = 2*MOVEMENT_MULTIPLIER;                         
            }
            else{
                 obby->Velocity.x = -2*MOVEMENT_MULTIPLIER;
            }
        }
        
  }
  
  

  void PE::ObjectSpriteIteration(Obj *objIterator){
              if( (objIterator->Id == OBJECT_JUMPER ) && objIterator->VarA > 0){ //TODO Object sprite iteration is here, incorrect area
                    int currentSpriteIt = objIterator->SpriteIt;
                    PE::ChangeObjSprite(&(*objIterator),objIterator->Id);
                    if(currentSpriteIt != objIterator->SpriteIt)objIterator->VarA--;
             }
             else if( (objIterator->Id == OBJECT_QUESTION_MARK ) && objIterator->VarA > 1){
                    int currentSpriteIt = objIterator->SpriteIt;
                    PE::ChangeObjSprite(&(*objIterator),objIterator->Id);
                    if(currentSpriteIt != objIterator->SpriteIt)objIterator->VarA--;
             } 
  }
  
  
  void PE::ApplyVelocity(){
         for(std::list<Obj>::iterator objIterator = (*GameObjectControllerPtr).ObjectIteratorBegin(); 
             objIterator !=  (*GameObjectControllerPtr).ObjectIteratorEnd(); 
             objIterator++){
                if(objIterator->Type != STATIC){  
                    if(objIterator->Type == PLAYER || objIterator->Type == MOB){
                         if(objIterator->Type == MOB)
                              PE::ApplyAI(&(*objIterator));                 
                         Collision_Handling(&(*objIterator));
                    }
                    else{ //Type: OBJECT
                         objIterator->Pos += objIterator->Velocity;
                         PE::ObjectSpriteIteration(&(*objIterator));
                    }
                }
         }  
  }
  
  double PE::FrictionHandler(Obj *afflicted,Vector *idealVelocity,Obj *down){ //returns change
       if(afflicted == NULL || down == NULL){
           Debug("PE::FrictionHandler Null Object");
           return 0.0;
       }
  
       double xbefore = (double)idealVelocity->x;
       if((down->Type == STATIC || down->Type == OBJECT) && (afflicted->Type == MOB || afflicted->Type == PLAYER)){
            idealVelocity->x *= STD_GROUND_FRICTION;
       }
       return (idealVelocity->x - xbefore);
  }
  
  void PE::ChangeObjSprite(Obj * obby, int spritecode){
       int tmp=0;
       if(pDisplay->GetAnimationSurface(spritecode,&tmp) != NULL){
            if(obby->Sprite == spritecode){
                 pDisplay->IterateAnimation(obby->Sprite,&obby->SpriteIt,&obby->LastSpriteIt,pTimer->pollTimer()); //iterate if sprite is already used
            }
            else{
                 pDisplay->ResetAnimation(spritecode,&obby->SpriteIt,&obby->LastSpriteIt,pTimer->pollTimer());
                 obby->Sprite = spritecode;
            }
            Vector oldDim = obby->Dim;
            Vector oldPos = obby->Pos;
            
            Vector newDim = Vector(pDisplay->GetAnimationSurface(obby->Sprite,&obby->SpriteIt)->w,pDisplay->GetAnimationSurface(obby->Sprite,&obby->SpriteIt)->h);
            obby->Dim = newDim;
            
            if(obby->Velocity.x <= 0){
                 obby->Pos = oldPos - (newDim-oldDim);
            }
            else{
                 obby->Pos = oldPos + (newDim-oldDim);
            }
      }
      else{
           Debug("func ChangeObjSprite: Invalid Sprite Code");
      }
         
  }
  
  void PE::Collision_HandlingVerticalCase(Obj *obby, CollisionObj * collb,CollisionObj * touchedcollb, Vector * idealPos, Vector * idealVec){
               if(collb->up != NULL && collb->down == NULL){ //UP 
                    if(idealVec->y < -MAX_VELOCITY)idealVec->y = -MAX_VELOCITY*3/4.0;
                    if((collb->up)->Id == OBJECT_QUESTION_MARK && (collb->up)->VarA == 0){
                        (collb->up)->VarA = 3;
                    }
                    idealPos->y = (collb->up)->Pos.y+(collb->up)->Dim.y;
                    idealVec->y = 2*MOVEMENT_MULTIPLIER;
                    touchedcollb->up = (Obj *)1;
               
                    
               }
               else if(collb->down != NULL && collb->up == NULL){//DOWN
                    FrictionHandler(obby,&*idealVec,collb->down);
                    if(idealVec->y > MAX_VELOCITY)idealVec->y = MAX_VELOCITY*3/4.0;
                    /*
                    if(obby->Type == PLAYER && (collb->down)->Type == MOB && PE::pPlayer->pKeyboard->Down == true){
                         PE::GameObjectControllerPtr->RemoveObjectP((Obj *)collb->down);
                    }
                    fails make it work
                    */
                    if((collb->down)->Id == OBJECT_JUMPER  && (collb->down)->VarA == 0){
                        (collb->down)->VarA = 3;
                        idealVec->y = -MAX_VELOCITY*1.5;
                    }
                    else{ 
                        idealVec->y = 0;
                    }
                    
                    idealPos->y = ((collb->down)->Pos.y)-(obby->Dim.y);
                    *collb = InvasiveCollisionCheck(obby, *idealPos);
                    touchedcollb->down = (Obj *)1;
               }
  }
  void PE::Collision_HandlingHorizontalCase(Obj *obby, CollisionObj * collb,CollisionObj * touchedcollb, Vector * idealPos, Vector * idealVec){
               if(collb->left != NULL && collb->right == NULL){ //LEFT 
                    idealPos->x = (collb->left)->Pos.x+(collb->left)->Dim.x;
                    idealVec->x = 0;
                    touchedcollb->left = (Obj *)1;
               }
               else if(collb->right != NULL && collb->left == NULL){//RIGHT
                    idealPos->x = (collb->right)->Pos.x-(obby->Dim.x);
                    idealVec->x = 0;
                    touchedcollb->right = (Obj *)1;
               }
  }
  
  void PE::Collision_Handling(Obj * obby){  //player,mob
       CollisionObj collb;
       CollisionObj touchedcollb; //Only used to record which sides have been touched
       Vector idealPos =  obby->Pos + obby->Velocity;
       Vector idealVec = obby->Velocity;
       
       touchedcollb.left = 0;
       touchedcollb.right = 0;
       touchedcollb.up = 0;
       touchedcollb.down = 0;
       
       collb = InvasiveCollisionCheck(obby, obby->Pos + obby->Velocity);
       if(collb.CollisionTrue()){                    
           if(obby->AirHeight == 0){ 
               PE::Collision_HandlingVerticalCase(obby,&collb,&touchedcollb,&idealPos,&idealVec);
               PE::Collision_HandlingHorizontalCase(obby,&collb,&touchedcollb,&idealPos,&idealVec);
           }
           else{
               PE::Collision_HandlingHorizontalCase(obby,&collb,&touchedcollb,&idealPos,&idealVec);
               collb = InvasiveCollisionCheck(obby, idealPos + idealVec);
               PE::Collision_HandlingVerticalCase(obby,&collb,&touchedcollb,&idealPos,&idealVec);
           }
           
           if(( collb = InvasiveCollisionCheck(obby, idealPos)).CollisionTrue()){ //Bad Collision
                   /*if(collb.left != NULL && collb.right != NULL){
                      while(collb.CollisionTrue()){
                           if(obby->Velocity.x < 0)
                                idealPos.x+=MIN_INCREMENT;
                           else
                               idealPos.x-=MIN_INCREMENT;
                           collb = InvasiveCollisionCheck(obby,idealPos);
                       }
                       Debug("func Collision_Handling: Unwanted Collision Case VERTICAL");
                   }
                   if(collb.up != NULL && collb.down != NULL){
                      while(collb.CollisionTrue()){
                           if(obby->Velocity.y < 0)
                                idealPos.y+=MIN_INCREMENT;
                           else
                               idealPos.y-=MIN_INCREMENT;                   
                           collb = InvasiveCollisionCheck(obby,idealPos);
                       }
                       Debug("func Collision_Handling: Unwanted Collision Case HORIZONTAL");
                   }*/
                   if(collb.down != NULL){
                      while((collb = InvasiveCollisionCheck(obby,idealPos)).CollisionTrue())
                            --idealPos.y; //go up                   
                   }
                   
                   idealVec *= 0;
                   touchedcollb.down = (Obj *)1;
                   touchedcollb.left = (Obj *)1;
           }
           
           
       }
       else{
            //adding velocity casues no problems
       }
       
       if(obby->Type == PLAYER || obby->Type == MOB){
           int curheight = 0;
           if(obby->Type == PLAYER)
                curheight  = PE::AirHeight(obby,idealPos);
           else{
                curheight =  PE::DirtyAirHeight(obby,idealPos);
           }
           
           Vector diffPos = idealPos - obby->Pos;
           Vector diffVec = idealVec - obby->Velocity;
           
           obby->AirHeight = curheight;
           
           //Sprite Handling
           if(curheight > 0){        
               if(obby->Sprite == obby->SpriteMap->standLeft || 
                  obby->Sprite == obby->SpriteMap->skidLeft || 
                  obby->Sprite == obby->SpriteMap->jumpLeft || 
                  obby->Sprite == obby->SpriteMap->walkLeft){
                    ChangeObjSprite(obby,obby->SpriteMap->jumpLeft); 
               }
               else{
                    ChangeObjSprite(obby,obby->SpriteMap->jumpRight); 
               }
           }
           
           if(curheight == 0){
                if(idealVec.x > MINRUNVELOCITY){
                    ChangeObjSprite(obby,obby->SpriteMap->walkRight);
               }
               else if(idealVec.x < -MINRUNVELOCITY){
                    ChangeObjSprite(obby,obby->SpriteMap->walkLeft);
               }
               else if(idealVec.x > -MINRUNVELOCITY && idealVec.x < MINRUNVELOCITY){
                      if(diffVec.x < 0){
                          ChangeObjSprite(obby,obby->SpriteMap->standRight);
                      }
                      else if(diffVec.x > 0){
                          ChangeObjSprite(obby,obby->SpriteMap->standLeft);
                      }
                      else if(obby->Sprite == obby->SpriteMap->jumpLeft){
                           ChangeObjSprite(obby,obby->SpriteMap->standLeft);
                      }
                      else if(obby->Sprite == obby->SpriteMap->jumpRight){
                            ChangeObjSprite(obby,obby->SpriteMap->standRight);
                      }        
               }

           }
       }
       obby->LastPos = obby->Pos;
       obby->LastVelocity = obby->Velocity;
       
       obby->Pos = idealPos;
       obby->Velocity = idealVec;
  }
  
  
  
  CollisionObj PE::InvasiveCollisionCheck(Obj *obby, Vector TestPos){ /*todo, improve for platforms*/
  
        CollisionObj collobj(obby);
         for(std::list<Obj>::iterator objIterator = (*GameObjectControllerPtr).ObjectIteratorBegin(); 
                                      objIterator !=  (*GameObjectControllerPtr).ObjectIteratorEnd(); 
                                      objIterator++)
         {
                if(&(*objIterator) != obby && 
                    abs((int)(obby->Pos.x-objIterator->Pos.x)) < BLOCK_SIZE*2  && abs((int)(obby->Pos.y-objIterator->Pos.y)) < BLOCK_SIZE*2  && 
                    
                    SDL_CollideRect( pDisplay->GetAnimationSurface(obby->Sprite,&obby->SpriteIt),(int)TestPos.x, (int)TestPos.y,
                                     pDisplay->GetAnimationSurface(objIterator->Sprite,&objIterator->SpriteIt), (int)objIterator->Pos.x, (int)objIterator->Pos.y)){

                      int dx = (int)abs((int)(TestPos.x - objIterator->Pos.x));
                      int dy = (int)abs((int)(TestPos.y - objIterator->Pos.y));
                      
                      if(dx > dy){ //HORIZONTAL COLLISION
                            if(dx > COLLISION_THRESHOLD ){
                                if(TestPos.x < objIterator->Pos.x){ //RIGHT
                                     //if(collobj.right != NULL) PROBLEM? <-------Investigate
                                     collobj.right = &(*objIterator);
                                     continue;
                                }
                                else{//LEFT
                                     collobj.left = &(*objIterator);
                                     continue;
                                }
                            }
                      }
                      else { //VERTICAL COLLISION
                            
                                if(TestPos.y < objIterator->Pos.y){ //DOWN
                                     collobj.down = &(*objIterator);
                                     continue;
                                }
                                else{//UP
                                     collobj.up = &(*objIterator);
                                     continue;
                                }
                            
                      }
                 }
         }  
        return collobj;
  }
  
  int PE::AirHeight(Obj *obby, Vector TestPos){ //16 passes
       Vector HeightTestPos = TestPos;
       while(!InvasiveCollisionCheck(obby, HeightTestPos).CollisionTrue() && (HeightTestPos.y - TestPos.y < BLOCK_SIZE*5)) //maximum 5 passes
            HeightTestPos.y+=BLOCK_SIZE;
       HeightTestPos.y-=BLOCK_SIZE;
       
       while(!InvasiveCollisionCheck(obby, HeightTestPos).CollisionTrue() && (HeightTestPos.y - TestPos.y < BLOCK_SIZE*10)) //maximum 11 passes
            HeightTestPos.y+=3;
       HeightTestPos.y-=3;
       
       return (int)(HeightTestPos.y - TestPos.y);  
  }
  int PE::DirtyAirHeight(Obj *obby,Vector HeightTestPos){ //666 in air, 0 if not
       HeightTestPos.y+=2;
       if(InvasiveCollisionCheck(obby, HeightTestPos).CollisionTrue()){return 0;}
       return 666;
  }
