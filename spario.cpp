#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <time.h>
#include <list>
#include <unistd.h>
#include "spario.h"
/*............................Global Declarations..........................*/
char programBasePath[256];
Display g_display = Display(SCREEN_W*BLOCK_SIZE,SCREEN_H*BLOCK_SIZE,"Spario");
Map g_map = Map();
Keyboard g_keyboard = Keyboard();
Sound g_sound = Sound();
Timer g_timer = Timer();
CameraController g_CameraController;
GameObjectController g_GameObjectController(&g_display,&g_CameraController);
MapObjGameTranslator g_MapObjGameTranslator(&g_display, &g_map, &g_GameObjectController,&g_CameraController);
PlayerController g_PlayerController(&g_keyboard,&g_GameObjectController,&g_MapObjGameTranslator);

PhysicsEngine g_PhysicsEngine(&g_display, &g_GameObjectController,&g_PlayerController,&g_timer);

/*............................Global Declarations..........................*/

void init(){
    srand ( time(NULL) );
    //------------------Mario----------------------------------
    g_display.LoadFont("/art/blackWolf.ttf",16);

    g_display.NewAnimation(198,0);
    g_display.PushAnimationImage(198,"/art/sprites/mariod.bmp");

    g_display.NewAnimation(199,0);
    g_display.PushAnimationImage(199,"/art/sprites/mariol.bmp");

    g_display.NewAnimation(200,0);
    g_display.PushAnimationImage(200,"/art/sprites/marior.bmp");

    g_display.NewAnimation(201,100);
    g_display.PushAnimationImage(201,"/art/sprites/mariowr1.bmp");
    g_display.PushAnimationImage(201,"/art/sprites/mariowr2.bmp");
    g_display.PushAnimationImage(201,"/art/sprites/mariowr3.bmp");

    g_display.NewAnimation(202,100);
    g_display.PushAnimationImage(202,"/art/sprites/mariowl1.bmp");
    g_display.PushAnimationImage(202,"/art/sprites/mariowl2.bmp");
    g_display.PushAnimationImage(202,"/art/sprites/mariowl3.bmp");

    g_display.NewAnimation(203,0);
    g_display.PushAnimationImage(203,"/art/sprites/mariojl.bmp");

    g_display.NewAnimation(204,0);
    g_display.PushAnimationImage(204,"/art/sprites/mariojr.bmp");

    g_display.NewAnimation(205,0);
    g_display.PushAnimationImage(205,"/art/sprites/marioskl.bmp");

    g_display.NewAnimation(206,0);
    g_display.PushAnimationImage(206,"/art/sprites/marioskr.bmp");
    //------------------Mario----------------------------------

    g_display.NewAnimation(1,0);
    g_display.PushAnimationImage(1,"/art/sprites/block.bmp");

    g_display.NewAnimation(2,0);
    g_display.PushAnimationImage(2,"/art/sprites/brick.bmp");

    g_display.NewAnimation(3,0);
    g_display.PushAnimationImage(3,"/art/sprites/sky.bmp");

    g_display.NewAnimation(99,0);
    g_display.PushAnimationImage(3,"/art/sprites/bullseye.bmp");


    g_display.NewAnimation(OBJECT_JUMPER,100);
    g_display.PushAnimationImage(OBJECT_JUMPER,"/art/sprites/jumper1.bmp");
    g_display.PushAnimationImage(OBJECT_JUMPER,"/art/sprites/jumper2.bmp");
    g_display.PushAnimationImage(OBJECT_JUMPER,"/art/sprites/jumper3.bmp");

    g_display.NewAnimation(MOB_GOOMPA,100);
    g_display.PushAnimationImage(MOB_GOOMPA,"/art/sprites/goom1.bmp");
    g_display.PushAnimationImage(MOB_GOOMPA,"/art/sprites/goom2.bmp");

    g_display.NewAnimation(MOB_GOOMPA_DEAD,50);
    g_display.PushAnimationImage(MOB_GOOMPA_DEAD,"/art/sprites/goomdead.bmp");

    g_display.NewAnimation(OBJECT_QUESTION_MARK,100);
    g_display.PushAnimationImage(OBJECT_QUESTION_MARK,"/art/sprites/qm1.bmp");
    g_display.PushAnimationImage(OBJECT_QUESTION_MARK,"/art/sprites/qm2.bmp");
    g_display.PushAnimationImage(OBJECT_QUESTION_MARK,"/art/sprites/qm3.bmp");


    g_display.NewAnimation(MOB_MAR_STANDL,0);
    g_display.PushAnimationImage(MOB_MAR_STANDL,"/art/sprites/standl.bmp");

    g_display.NewAnimation(MOB_MAR_STANDR,0);
    g_display.PushAnimationImage(MOB_MAR_STANDR,"/art/sprites/standr.png");

    g_display.NewAnimation(MOB_MAR_WALKR,70);
    g_display.PushAnimationImage(MOB_MAR_WALKR,"/art/sprites/Runr0.bmp");
    g_display.PushAnimationImage(MOB_MAR_WALKR,"/art/sprites/Runr1.bmp");
    g_display.PushAnimationImage(MOB_MAR_WALKR,"/art/sprites/Runr2.bmp");
    g_display.PushAnimationImage(MOB_MAR_WALKR,"/art/sprites/Runr3.bmp");

    g_display.NewAnimation(MOB_MAR_WALKL,70);
    g_display.PushAnimationImage(MOB_MAR_WALKL,"/art/sprites/Runl0.bmp");
    g_display.PushAnimationImage(MOB_MAR_WALKL,"/art/sprites/Runl1.bmp");
    g_display.PushAnimationImage(MOB_MAR_WALKL,"/art/sprites/Runl2.bmp");
    g_display.PushAnimationImage(MOB_MAR_WALKL,"/art/sprites/Runl3.bmp");

    g_display.NewAnimation(OBJ_PLATFORM_1,0);
    g_display.PushAnimationImage(OBJ_PLATFORM_1,"/art/sprites/platform1.bmp");

    g_display.NewAnimation(OBJ_PLATFORM_2,0);
    g_display.PushAnimationImage(OBJ_PLATFORM_2,"/art/sprites/platform2.bmp");

    g_display.NewAnimation(OBJ_PLATFORM_3,0);
    g_display.PushAnimationImage(OBJ_PLATFORM_3,"/art/sprites/platform1.bmp");

    g_display.Clear();
    g_keyboard.Clear();
    g_map.load("","main.map");
    g_timer.startTimer();
}



int main(int argc, char **argv){
    char TEXT[128];
    double t_start,t_elasped,t_volume,t_total;
    double t_delay = 1000.0;
    double LastRenderedTime = g_timer.pollTimer();

    if(argc >= 1){
        int programBaseLength = strlen(argv[0]);
        if(programBaseLength <= 256){
            memcpy (programBasePath,argv[0], programBaseLength );
        }
        else{
             DebugMsg("Executable Path Length is Over 256 Characters");
        }
        bool foundSlash = false;
        for(int i=programBaseLength-1;i>=0;i--){
                if(programBasePath[i] == 47 || programBasePath[i] == 92){ //[47 /], [92 \]
                      programBasePath[i] = 0;
                      foundSlash = true;
                      break;
                }
        }
        if(!foundSlash)
             memcpy (programBasePath, "", 1);
        g_display.FilePath(programBasePath);
    }
    init();


    int t_i;
    double t_d[32];

    while(1){
        t_start = g_timer.pollTimer();

        t_i = 0;

        g_PlayerController.KeyboardUpdate();
        g_PhysicsEngine.ApplyGravity();
        g_PhysicsEngine.ApplyVelocity(); // t_d[t_i++] =  g_timer.pollTimer() - t_start; t_start = g_timer.pollTimer();

        g_CameraController.SetCamera(g_PlayerController.PlayerPos());
        //g_CameraController.SetCamera(Vector(7,27)*BLOCK_SIZE);

        g_MapObjGameTranslator.MapObjTranslate();
        g_MapObjGameTranslator.ObjMapTranslate();



        //g_GameObjectController.DebugObjects(); return 0;

        if(g_timer.pollTimer() - LastRenderedTime > 1000.0/60.00){
            g_display.Clear();
            g_GameObjectController.RenderObjects();
            int ii=-1;
            if(t_volume > 100){t_delay = t_total/t_volume; t_total = 0; t_volume=0; }
            sprintf(TEXT,"Frame Time: %2.0ffps, %2.2fms",1000.0/t_delay,t_delay);
            g_display.DrawString(TEXT,0,(++ii)*20,0,0x00FF00);
            sprintf(TEXT,"Time Elasped: %6.1fs",g_timer.pollTimer()/1000);
            g_display.DrawString(TEXT,0,(++ii)*20,0,0x00FF00);
            sprintf(TEXT,"Objects: %i",g_GameObjectController.CountObjects());
            g_display.DrawString(TEXT,0,(++ii)*20,0,0x00FF00);
            sprintf(TEXT,"Player Pos:%2.3f,%2.3f",g_PlayerController.PlayerPos().x,g_PlayerController.PlayerPos().y);
            g_display.DrawString(TEXT,0,(++ii)*20,0,0x00FF00);
            sprintf(TEXT,"Player Vel:%2.3f,%2.3f",g_PlayerController.PlayerVelocity().x,g_PlayerController.PlayerVelocity().y);
            g_display.DrawString(TEXT,0,(++ii)*20,0,0x00FF00);
            sprintf(TEXT,"Player LVel:%2.3f,%2.3f",g_PlayerController.PlayerLastVelocity().x,g_PlayerController.PlayerLastVelocity().y);
            g_display.DrawString(TEXT,0,(++ii)*20,0,0x00FF00);
            sprintf(TEXT,"PHeight: %i",g_PhysicsEngine.AirHeight(g_PlayerController.PlayerPt(),g_PlayerController.PlayerPos()));
            g_display.DrawString(TEXT,0,(++ii)*20,0,0x00FF00);
            for(int iii=0;iii < t_i; iii++){
            sprintf(TEXT,"%3.0f",t_d[iii]);
            g_display.DrawString(TEXT,0,(++ii)*20,0,0x00FF00);
            }
            g_display.Render();
            LastRenderedTime = g_timer.pollTimer();
        }

        /*Timer*/
        t_elasped = g_timer.pollTimer() -  t_start;
        t_total += t_elasped;
        t_volume++;
        /*Timer*/

        double delay = (int)(1000.0/40.00-t_elasped);
        if(delay <0){delay=0; Debug("Elasped time > 25ms");}


        SDL_Delay((int)delay/2);

        if(g_keyboard.Quit){
            break;
        }
        SDL_Delay((int)delay/2);

    }
    return 0;
}
/*

Split GameObjectController.objects using a quad tree.
.\
||
Map
-array of integers
-maps directly to tiles

Develop Game Handling Structures
-Restrictions,Scope
-Appropiate Sub-classes
-Pyramid Shape
-Flexability

*/



