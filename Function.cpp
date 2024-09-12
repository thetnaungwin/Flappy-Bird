#include "OOP.h"

void Window_Render::Text(std::string message, std::string fontFilePath, int fontSize, int x, int y){
    SDL_Color color={255,255,255,255};
    TTF_Font* font=TTF_OpenFont(fontFilePath.c_str(), fontSize);
    SDL_Surface* surface=TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Rect box={x,y, surface->w, surface->h};

    SDL_RenderCopy(renderer,texture,NULL,&box);
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
};
void Window_Render::playMusic(std::string filePath,int loops){
    music=Mix_LoadMUS(filePath.c_str());
    Mix_PlayMusic(music, loops);
};
void Window_Render::imageRender_one(std::string imagePath, int x, int width, int height){
    SDL_Surface* image=IMG_Load(imagePath.c_str());
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,image);
    SDL_Rect boxForImg={x, 0, width, height};
    SDL_RenderCopy(renderer,texture,NULL,&boxForImg);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
};
void Window_Render::imageRender_two(std::string imagePath, int x, int width, int height){
    SDL_Surface* image=IMG_Load(imagePath.c_str());
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,image);
    SDL_Rect boxForImg={x, 0, width, height};
    SDL_RenderCopy(renderer,texture,NULL,&boxForImg); 
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
};
void Window_Render::birdRender(std::string imagePath, int x, int y){
    SDL_Surface* bird=IMG_Load(imagePath.c_str());
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,bird);
    SDL_Rect boxForBird={x, y, bird->w, bird->h};
    SDL_RenderCopy(renderer,texture,NULL, &boxForBird);  

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(bird);
};
void Window_Render::pipe_upRender(std::string imagePath, int pipe_x, int pipe_y){
    SDL_Surface* pipe_up=IMG_Load(imagePath.c_str());
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer, pipe_up);
    SDL_Rect boxForPipeUp={ pipe_x, Height-pipe_up->h + pipe_y, pipe_up->w, pipe_up->h - pipe_y};
    SDL_RenderCopy(renderer, texture,NULL, &boxForPipeUp);
    //Collision algorithm
    if (bird_x >= pipe_x-25 && bird_y > (Height-pipe_up->h) + pipe_y && bird_x < pipe_x+pipe_up->w){
       StartMovement=false;
       StopImg=true;
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(pipe_up);
}
void Window_Render::pipe_downRender(std::string imagePath, int pipe_x, int pipe_y){
    SDL_Surface* pipe_down=IMG_Load(imagePath.c_str());
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer, pipe_down);
    SDL_Rect boxForPipeDown={pipe_x, 0, pipe_down->w, pipe_down->h - pipe_y};
    SDL_RenderCopy(renderer, texture, NULL, &boxForPipeDown);
    //Collision algorithm
    if (bird_x >= pipe_x-25 && bird_y < pipe_down->h - pipe_y && bird_x < pipe_x+pipe_down->w){
       StartMovement=false;
       StopImg=true;
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(pipe_down);
}
void Window_Render::UpdateFrame(){
    int time_to_wait=FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
      SDL_Delay(time_to_wait);
  
    float deltaVelocity = (SDL_GetTicks() - last_frame_time ) / 700.0f;
    last_frame_time = SDL_GetTicks();
    //Can use about FPS;
    if (!StopImg)
    {
        imageOne_x -=5;  
        imageTwo_x -=5;
        if (imageTwo_x<=0)
        {
           imageOne_x=0;
           imageTwo_x=Width;
           imageOne_x -=5; 
           imageTwo_x -=5;  
        }
    }
    if (StartMovement)
    {
        pipe_X1 -=5;
        pipe_X2 -=5;
        pipe_X3 -=5;
        if (pipe_X1<-40)
        {
           pipe_X1 =Width;
           pipe_up_Y1=rand()%100 +1;
        }
        if (pipe_X2<-40)
        {
           pipe_X2 =Width;
           pipe_up_Y2=rand()%100 +1;
        }
        if (pipe_X3<-40)
        {
           pipe_X3 =Width;
           pipe_up_Y3=rand()%100 +1;
        }
    }
    
    if (bird_y >= Height || bird_y <=0)
    {
        StartMovement=false;
        StopImg=true;
    }
    if (bird_x == pipe_X1 || bird_x == pipe_X2 || bird_x == pipe_X3)
    {
        if (!StopImg)
        {
            score ++;
        }
    }    
    //end of update
};
void Window_Render::setScreenRunning(bool ScreenRunningVal){
    ScreenRunning=ScreenRunningVal;
};
bool Window_Render::getScreenRunning(){
    return ScreenRunning;
};