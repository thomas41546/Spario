#include "map.h"

Map::Map(){
    Map::W = XMAP_W;
    Map::H = XMAP_H;      
    data = new unsigned int[Map::W*Map::H];
}

void Map::load(char *fbasepath,char *name){
    unsigned char *buff;
    unsigned long int blen = 0;
    
    char fname[512];
    if(fbasepath != NULL){
         sprintf(fname,"%s%s",fbasepath,name);
    }
    else{
         sprintf(fname,"%s",name);
    }
    
    
    readfile(&buff,&blen, fname);
    if(blen == Map::W*Map::H*sizeof(unsigned int)){
        memcpy((unsigned char *)data, buff, blen);
    }
    else{
         Debug("Error Looading Map: ");
         Debug((const char *)fname);
    }
    
    
    delete buff;
    
}
void Map::writeFlag(Vector Loc,int bit,bool state){//map[loc] set upper flag bit to state;
    if(Loc.x< Map::W && Loc.y < Map::H && Loc.x >= 0 && Loc.y >= 0 && bit < 16 && bit >= 0){
      data[(int)Loc.x+((int)Loc.y*Map::W)] = (data[(int)Loc.x+((int)Loc.y*Map::W)] & ~(1<<(bit+16)))|((int)state<<(bit+16));
    }
}
bool Map::readFlag(Vector Loc,int bit){
    if(Loc.x< Map::W && Loc.y < Map::H && Loc.x >= 0 && Loc.y >= 0 && bit < 16 && bit >= 0){
      return (bool)((data[(int)Loc.x+((int)Loc.y*Map::W)] >> (bit+16)) & 1);
    }
}
int Map::read(Vector Loc){ //excludes flags
    if(Loc.x< Map::W && Loc.y < Map::H && Loc.x >= 0 && Loc.y >= 0){
      return data[(int)Loc.x+((int)Loc.y*Map::W)] & 0xFFFF;
    }
}
int Map::getWidth(){
     return Map::W;
}
int Map::getHeight(){
     return Map::H;
}
