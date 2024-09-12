#include <bits/stdc++.h>
#include <ctime>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#define Width 550
#define Height 650
#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)

class Window_Render{
  private:
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;
    Mix_Music* music=nullptr;
    int imageOne_x=0;
    int imageTwo_x=Width;
    int pipe_up_Y1=0;
    int pipe_up_Y2=0;
    int pipe_up_Y3=0;
    int last_frame_time=0;
    bool ScreenRunning;

  public:
    int pipe_X1=Width;
    int pipe_X2=Width + 200;
    int pipe_X3=Width + 400;
    int bird_x=Width/2;
    int bird_y=Height/2;
    bool StartMovement=false;
    bool StopImg=false;
    int score=0;
    enum Direction { NONE, UP, DOWN};
    Direction currentDirection = NONE;
    Window_Render(){
        int flag=IMG_INIT_PNG;
        int initialStatus=IMG_Init(flag);
        if (SDL_Init(SDL_INIT_VIDEO)<0){
            std::cout<<"SDL could not be initialized"<<SDL_GetError()<<std::endl;
        }else if(TTF_Init()<0){
            std::cout<<"Text is not ready to run."<<TTF_GetError()<<std::endl;
        }else if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
            std::cout<<"Music is not ready to run."<<Mix_GetError()<<std::endl;
        }else if((initialStatus & flag) != flag){
            std::cout<<"Image is not ready to run."<<IMG_GetError()<<std::endl;
        }else{
            system("cls");
            std::cout<<"SDL video system is ready to go\n";
            window=SDL_CreateWindow("Flappy Bird",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width, Height, SDL_WINDOW_SHOWN);
            renderer=SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
            Window_Render::setScreenRunning(true);
            playMusic("music/stranger-things.MP3", -1);
            Mix_VolumeMusic(30);
        }
    };
    ~Window_Render(){
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        Mix_FreeMusic(music);
        TTF_Quit();
        SDL_Quit();
    };
    void all_programm_renderer(){
        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_RenderClear(renderer);

        imageRender_one("image/background.jpg",  imageOne_x, Width, Height);
        imageRender_two("image/background.jpg",  imageTwo_x, Width, Height);
        UpdateFrame();

        switch (currentDirection)
        {
        case NONE:
             if (!StopImg){
                birdRender("image/redbird-midflap.png", bird_x, bird_y);
            }
            break;
        case UP:
            if (!StopImg){
                bird_y -=5;
                StartMovement=true;
            }
            birdRender("image/redbird-upflap.png", bird_x, bird_y);
            break;
        case DOWN:
            if (!StopImg){
                bird_y +=5;
                StartMovement=true;
            }
            birdRender("image/redbird-downflap.png", bird_x, bird_y);
            break;
        };
        if (StartMovement)
        {  
            int pipe_up_Y1=rand()%100 +1;
            int pipe_up_Y2=rand()%100 +1;
            int pipe_up_Y3=rand()%100 +1;
        }; 
        //Pipe_distance 100
        pipe_upRender("image/pipe-greenup.png", pipe_X1, pipe_up_Y1);
        pipe_upRender("image/pipe-greenup.png", pipe_X2, pipe_up_Y2);
        pipe_upRender("image/pipe-greenup.png", pipe_X3, pipe_up_Y3); 
        pipe_downRender("image/pipe-greendown.png", pipe_X1, 1e2-pipe_up_Y1);
        pipe_downRender("image/pipe-greendown.png", pipe_X2, 1e2-pipe_up_Y2);
        pipe_downRender("image/pipe-greendown.png", pipe_X3, 1e2-pipe_up_Y3);
        //Score
        std::stringstream ss;
        ss<<score;
        std::string full=ss.str();
        Text(full, "font/ARIBLK.TTF", 50, Width/2  , Height/2 -300 );     

        if (StopImg==true && StartMovement==false)
        {
            if (bird_y != Height - 20)
            {
               currentDirection=NONE;
               bird_y +=5;
            }   
            birdRender("image/redbird-dead.png", bird_x, bird_y);
            birdRender("image/gameover.png", Width/2 - 50 , Height/2 - 100);
            birdRender("image/button_resume.png", Width/2 - 150  , Height/2);
            birdRender("image/button_quit.png", Width/2 + 100 , Height/2);
        }      

        SDL_RenderPresent(renderer);
    };
    void setScreenRunning(bool ScreenRunning);
    bool getScreenRunning();
    void Text(std::string message, std::string fontFilePath, int fontSize,int x, int y);
    void playMusic(std::string filePath,int loops);
    void imageRender_one(std::string imagePath, int x, int width, int height);
    void imageRender_two(std::string imagePath, int x, int width, int height);
    void birdRender(std::string imagePath,int x, int y);
    void pipe_upRender(std::string imagePath, int pipe_x, int pipe_y);
    void pipe_downRender(std::string imagePath, int pipe_x, int pipe_y);
    void UpdateFrame();
};