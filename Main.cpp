// g++ -I src/include -L src/lib main.cpp function.cpp -o sdlgame -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image
#include "OOP.h"

int WinMain(int argc, char* argv[]){
    time_t t;
    srand((unsigned)time(&t));
    SDL_Event event;
    //Class constructor and destructor
    Window_Render myGame;
    
    while (myGame.getScreenRunning())
    {
        myGame.all_programm_renderer();
        while (SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
            {
                myGame.setScreenRunning(false);
            }
            if (event.key.keysym.sym==SDLK_UP)
            {
                myGame.currentDirection=myGame.UP;
            }
            if (event.key.keysym.sym==SDLK_DOWN)
            {
                myGame.currentDirection=myGame.DOWN;
            }
            if(event.button.button == SDL_BUTTON_LEFT)
            {
               int x,y;
               Uint8 button;
               button=SDL_GetMouseState(&x, &y);
               if ((x > 382 && x < 488) && (y >330 && y < 390 ))
               {
                 myGame.setScreenRunning(false);
               }
               if ((x > 132 && x < 302) && (y >330 && y < 391 ))
               {
                  myGame.StartMovement=false;
                  myGame.StopImg=false;
                  myGame.bird_x=Width/2;
                  myGame.bird_y=Height/2;
                  myGame.pipe_X1=Width;
                  myGame.pipe_X2=Width + 200;
                  myGame.pipe_X3=Width + 400;
                  myGame.score=0;
               }
            }
        }
    };
    return 0;
};