#include "display.h"
#include <SDL/SDL.h>
#include <string.h>

char DEBUGMSG[128];
char g_fileName[512];

Display::Display(int screenWidth,int screenHeight, const char *caption){
   if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        sprintf (DEBUGMSG, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        DebugMsg(DEBUGMSG); 
        exit (1);
    }
    
    if (TTF_Init() < 0)
    {
        sprintf (DEBUGMSG, "Couldn't initialize TTF: %s\n", SDL_GetError ());
        DebugMsg(DEBUGMSG); 
        exit (1);
    }

    /* Set 640x480 16-bits video mode */
    Display::Screen = SDL_SetVideoMode (screenWidth, screenHeight, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (Display::Screen == NULL)
    {
        sprintf (DEBUGMSG, "Couldn't set video mode: %s\n",SDL_GetError ());
        DebugMsg(DEBUGMSG); 
        exit (2);
    }
   SDL_WM_SetCaption( caption, NULL );
   Display::Width = Display::Screen->w;
   Display::Height = Display::Screen->h;
}
void Display::LoadFont(const char *fName, int size){
    char * name = g_fileName;
    if(Display::BaseFilePath != NULL){
          sprintf(name,"%s%s",Display::BaseFilePath,fName);
    }
    else{
         sprintf(name,"%s",fName);
    } 
    Display::Font = TTF_OpenFont(name, size);
    if (Font == NULL)
    {
        sprintf (DEBUGMSG,"%s\n", TTF_GetError());
        DebugMsg(DEBUGMSG); 
        exit(1);
    }
}
void Display::DrawString(const char *text, int x, int y,int bg, int fg){
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor, backgroundColor;
    
    /* White text on a black background */
    
    foregroundColor.r = (fg & 0xFF0000) >> 4;
    foregroundColor.g = (fg & 0xFF00) >> 2;
    foregroundColor.b = (fg & 0x0000FF);
    
    backgroundColor.r = (bg & 0xFF0000) >> 4;
    backgroundColor.g = (bg & 0xFF00) >> 2;
    backgroundColor.b = (bg & 0x0000FF);
    
    /* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

    surface = TTF_RenderUTF8_Shaded(Display::Font, text, foregroundColor, backgroundColor);

    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }
    
    /* Blit the entire surface to the screen */

    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

    SDL_BlitSurface(surface, NULL, Display::Screen, &dest);
    
    /* Free the generated string image */

    SDL_FreeSurface(surface);
}

void Display::Caption(const char * caption){
     SDL_WM_SetCaption( caption, NULL );
}
void Display::FilePath(char * FilePath){
     Display::BaseFilePath = FilePath;
}



void Display::Clear(){
   SDL_FillRect(Display::Screen,NULL,0x000000);
}


void Display::DrawRectangle(int x,int y,int w,int h,int color){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_FillRect (Display::Screen, &rect, color);
}

void Display::Render(){
   SDL_Flip (Display::Screen);
}

void Display::NewAnimation(int referenceName,int delay){ //left off here
      struct Animation * animation = (struct Animation *)calloc(sizeof(struct Animation),1);
      
      animation->pos = 0;
      animation->delay = delay;
      animation->images = (SDL_Surface **)calloc(sizeof(SDL_Surface *)*32,1); //why 32?
      
      Display::Animations[referenceName] = animation;
}
void Display::PushAnimationImage(int referenceName,const char * fileName){
       Display::Animations[referenceName]->images[Display::Animations[referenceName]->pos++] = Display::LoadBMP(fileName);
}

void Display::IterateAnimation(int referenceName,int *userSpriteIt,double *userLastIt, double currenttimeMS){ //a delay of zero means no iteration
     if(Display::Animations[referenceName]->delay != 0 && currenttimeMS > *userLastIt + Display::Animations[referenceName]->delay){     
         ++(*userSpriteIt);
         if(*userSpriteIt >=  Display::Animations[referenceName]->pos)
              *userSpriteIt = 0;                                 
         *userLastIt = currenttimeMS;
     }
}

void Display::ResetAnimation(int referenceName,int *userSpriteIt,double *userLastIt,double seedtimeMS){
     *userSpriteIt = 0;
     *userLastIt = seedtimeMS;
}
SDL_Surface* Display::GetAnimationSurface(int referenceName,int *userSpriteIt){
     if(Display::Animations[referenceName] == NULL){return NULL;}
     return Display::Animations[referenceName]->images[*userSpriteIt];
}

void Display::DrawAnimation(int x, int y, int referenceName, int *userSpriteIt){
     Display::DrawImage (x, y, Display::GetAnimationSurface(referenceName,userSpriteIt));
}


void Display::LoadBitmapA(const char *referenceName,const char *fileName){
   Display::Bitmaps[referenceName] = Display::LoadBMP(fileName);
}
void Display::LoadBitmapI(int referenceName,const char *fileName){
   Display::BitmapsI[referenceName] = Display::LoadBMP(fileName);
}

SDL_Surface * Display::LoadBMP(const char *fName){
   SDL_Surface* temp; 
   SDL_Surface *image;
   
   char * fileName = g_fileName;
   if(Display::BaseFilePath != NULL){
        sprintf(fileName,"%s%s",Display::BaseFilePath,fName);
   }
   else{
        sprintf(fileName,"%s",fName);
   }
   temp = IMG_Load(fileName);
   if ( temp == NULL) {
        sprintf (DEBUGMSG, "Unable to load bitmap: %s\n",fileName);
        DebugMsg(DEBUGMSG);
        exit(250);
   }
   SDL_SetColorKey( temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255) ); 
   image = SDL_DisplayFormatAlpha(temp);
   SDL_FreeSurface(temp);
   return image;
}


SDL_Surface* Display::GetBitmapSurface(int referenceName){
     return Display::BitmapsI[referenceName];
}

SDL_Surface* Display::GetBitmapSurface(const char * referenceName){
     return Display::Bitmaps[referenceName];
}

void Display::DrawBitmap(int x,int y,int referenceName){
     Display::DrawImage(x, y, Display::BitmapsI[referenceName]);
}

void Display::DrawBitmap(int x,int y,const char *referenceName){
     Display::DrawImage(x, y, Display::Bitmaps[referenceName]);
}

void Display::DrawImage(int x, int y, SDL_Surface* bitmap){
   SDL_Rect dstrect;
   dstrect.x = x;
   dstrect.y = y;
   dstrect.w = (Display::Screen)->w;
   dstrect.h = (Display::Screen)->h;
   SDL_BlitSurface(bitmap, NULL, Display::Screen, &dstrect);
}







