#include "obj.h"

Obj::Obj(Vector iPos, Vector ivelocity,Vector iDim,Vector imapblock,int iID,int itype){
        Obj::Init(iPos,ivelocity,iDim,imapblock,iID,itype);           
}

Obj::Obj(){
        Obj::Init(Vector(0,0),Vector(0,0),Vector(0,0),Vector(BLOCK_SIZE,BLOCK_SIZE),0,STATIC);
}

void Obj::Init(Vector iPos, Vector ivelocity,Vector iDim,Vector imapblock,int iID,int itype){
        Obj::Pos = iPos;
        Obj::LastPos = iPos;
        Obj::Velocity = ivelocity;
        Obj::LastVelocity = ivelocity;
        Obj::MapBlock = imapblock;
        Obj::Dim = iDim;
        Obj::Type = itype;
        Obj::Id = iID;
        Obj::Sprite = iID;
        Obj::LastSpriteChange = 0;
        Obj::AirHeight = 0;
        Obj::SpriteIt = 0;
        Obj::LastSpriteIt = 0.0;
        if(itype == MOB || itype == PLAYER){
             Obj::AllocSpriteMap();
        }
        else{
             Obj::SpriteMap = NULL;
        }
}
void Obj::AllocSpriteMap(){
     if(Obj::SpriteMap == NULL)
           Obj::SpriteMap = (struct SSpriteMap *)calloc(sizeof(struct SSpriteMap),1);
}
void Obj::DeAllocSpriteMap(){
     if(Obj::SpriteMap != NULL)
           delete Obj::SpriteMap;
}


bool objSorter(const Obj &f1, const Obj &f2) { //physics engine process priority
     return (f1.Type < f2.Type);
};


