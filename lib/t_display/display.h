#ifndef DISPLAY
#define DISPLAY
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <map>
#include "../../lib/global.h"

struct Animation{
       int pos; //number of images
       int delay; //ms
       SDL_Surface** images; //limit 32
};

class Display{
public:
  int Width;
  int Height;
  char * BaseFilePath;
  TTF_Font* Font;
  SDL_Surface* Screen;
  std::map<const char*, SDL_Surface*> Bitmaps;
  std::map<int, SDL_Surface*> BitmapsI;
  
  std::map<int, struct Animation *> Animations;
  
  
  Display(int,int,const char *);
  
  SDL_Surface * LoadBMP(const char *);
  void LoadFont(const char *, int);
  void DrawString(const char *, int , int,int,int);

  void FilePath(char * );
  void Caption(const char *);
  void LoadBitmapA(const char *,const char *);
  void LoadBitmapI(int ,const char *);
 

  
  
  void NewAnimation(int,int);
  void PushAnimationImage(int,const char *);
  void IterateAnimation(int,int *,double *,double);
  void ResetAnimation(int,int *,double *,double);
  void DrawAnimation(int,int,int,int *);
  SDL_Surface* GetAnimationSurface(int, int *);
  
  
  void Clear();
  void Render();
  void DrawRectangle(int,int,int,int,int);
  
  SDL_Surface* GetBitmapSurface(int);
  SDL_Surface* GetBitmapSurface(const char *);

  void DrawBitmap(int,int,const char *);
  void DrawBitmap(int,int,int);
  
  void DrawText(const char, int, int);
  void DrawImage(int , int , SDL_Surface*);
  
  
  
};
#endif
