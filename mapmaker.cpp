#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <windows.h>
#include <time.h>
#include <list.h>

#include "mapmaker.h"

#define DBGB 1024

#define MAP_W 40
#define MAP_H 40




#define BLOCK_SIZE 32

/*............................DEBUG..........................*/
char DEBUGMSGX[DBGB];
char TEXT[256];

void dbgc(){
     memset (DEBUGMSGX,0,DBGB);;
}

void dbgp(){
      MessageBox (0, DEBUGMSGX, "DEBUG", MB_ICONHAND);
      dbgc();
}

void dbgm(const char *in,int a, int b, int c){
     sprintf(DEBUGMSGX,"%s%s%i,%i,%i\n",DEBUGMSGX,in,a,b,c);
     dbgp();
}

void DebugMsg(const char *in){
     MessageBox (0, in, "DEBUG", MB_ICONHAND);
}

void Debug(char const *bacon){}

/*............................DEBUG..........................*/


/*............................Global Declarations..........................*/
int *map = new int[MAP_W*MAP_H];

Display display = Display(SCREEN_W*BLOCK_SIZE,SCREEN_H*BLOCK_SIZE,"Spario Map Maker");
Keyboard keyboard = Keyboard();
Sound sound = Sound();
/*............................Global Declarations..........................*/

const int TILES_C = 8;

int it = 0;
int tileMap[TILES_C] = {1,2,3,100,101,103,104,110};



class Bullseye{
      public:
             int x,y; //in blocks
             
             Bullseye(){}
             
};
Bullseye bs = Bullseye();


/*............................Class Functions..........................*/

/*............................Class Functions..........................*/


void ClearMap(){
     for(int i=0;i < MAP_W*MAP_H;i++){
             map[i] = 0;
     }
}

void RenderScreen(){
     for(int y=bs.y;y<bs.y+SCREEN_H;y++){
          for(int x=bs.x;x<bs.x+SCREEN_W;x++){
                  if(x >= 0 && y >= 0 && x < MAP_W && y < MAP_H && map[x+y*MAP_W] >= 0 && map[x+y*MAP_W] != 99 && map[x+y*MAP_W] > 0){      
                        display.DrawBitmap((x-bs.x)*BLOCK_SIZE,(y-bs.y)*BLOCK_SIZE,map[x+y*MAP_W]);
                  }
          }
     }
}
void DrawBullseye(){
     display.DrawBitmap(SCREEN_W/2*BLOCK_SIZE,SCREEN_H/2*BLOCK_SIZE,tileMap[it]);
     display.DrawBitmap(SCREEN_W/2*BLOCK_SIZE,SCREEN_H/2*BLOCK_SIZE,99);
}


void KeyInput(){
     keyboard.Poll();
     if(keyboard.Up){
         bs.y--;
     }
     else if(keyboard.Down){
        bs.y++;
     }
     else if(keyboard.Left){
         bs.x--;
     }
     else if(keyboard.Right){
         bs.x++;
     }
     else if(keyboard.Space){
          if( ((bs.x+(SCREEN_W/2))+(bs.y+(SCREEN_H/2))*MAP_W) >=0 && ((bs.x+(SCREEN_W/2))+(bs.y+(SCREEN_H/2))*MAP_W) < MAP_W*MAP_H){
          map[(bs.x+(SCREEN_W/2))+(bs.y+(SCREEN_H/2))*MAP_W] = tileMap[it];
          }
     }
     else if(keyboard.r){
          it++;
          if(it > TILES_C){it = 0;}
     }
     else if(keyboard.p){
          if( ((bs.x+(SCREEN_W/2))+(bs.y+(SCREEN_H/2))*MAP_W) >=0 && ((bs.x+(SCREEN_W/2))+(bs.y+(SCREEN_H/2))*MAP_W) < MAP_W*MAP_H){
              map[(bs.x+(SCREEN_W/2))+(bs.y+(SCREEN_H/2))*MAP_W] = 0;
          }
     }
     
     else if(keyboard.s){ //DEBUG
         writefile((char *)map,sizeof(int)*MAP_W*MAP_H,"main.map");
         exit(0);
     }
     
     
     keyboard.Clear();
}





void init(){
    srand ( time(NULL) );
    display.LoadBitmapI(99,"art/sprites/bullseye.bmp");
    display.LoadBitmapI(1,"art/sprites/block.bmp");
    display.LoadBitmapI(2,"art/sprites/brick.bmp");
    display.LoadBitmapI(3,"art/sprites/sky.bmp");
    display.LoadBitmapI(100,"art/sprites/jumper1.bmp");
    display.LoadBitmapI(101,"art/sprites/goom1.bmp");
    display.LoadBitmapI(103,"art/sprites/qm1.bmp");
    display.LoadBitmapI(104,"art/sprites/standr.bmp");
    display.LoadBitmapI(110,"art/sprites/platform3.bmp");
    display.Clear();
    
    keyboard.Clear();
}



int main(int argc, char **argv){
    init();
    ClearMap();
    
    unsigned char *buff;
    unsigned long int blen = 0;
    readfile(&buff,&blen, "main.map");
    if(blen == MAP_W*MAP_H*sizeof(int)){
       memcpy((unsigned char *)map, buff, blen);
    }
    else{
       ClearMap();
    }
    
    while(!keyboard.Quit){
        display.Clear();
        KeyInput(); 
        
        RenderScreen();
        DrawBullseye();
        /*
          
        sprintf(TEXT,"X,Y: %i,%i",bs.x,bs.y); 
        display.DrawString(TEXT,0,0,0,0x00FF00);
        
        sprintf(TEXT,"BLOCK: %i",it); 
        display.DrawString(TEXT,0,20,0,0x00FF00);
*/
        display.Render();
        SDL_Delay(50);
    }
    

    return 0;
}


