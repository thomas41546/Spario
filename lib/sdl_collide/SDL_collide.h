#ifndef _SDL_COLLIDE_h
#define _SDL_COLLIDE_h
#include "../../lib/global.h"
#include <SDL/SDL.h>

int SDL_CollideTransparentPixelTest(SDL_Surface *surface , int u , int v);
int SDL_CollidePixel(SDL_Surface *as , int ax , int ay , SDL_Surface *bs , int bx , int by);
int SDL_CollideRect(SDL_Surface *as , int ax , int ay , SDL_Surface *bs , int bx , int by);
int SDL_CollideBoundingBox(SDL_Surface *sa , int ax , int ay , SDL_Surface *sb , int bx , int by);
int SDL_CollideBoundingBox(SDL_Rect a , SDL_Rect b);
int SDL_CollideBoundingCircle(int x1 , int y1 , int r1 ,int x2 , int y2 , int r2 , int offset);
int SDL_CollideBoundingCircle(SDL_Surface *a , int x1 , int y1 ,SDL_Surface *b , int x2 , int y2 ,int offset);

#endif 
