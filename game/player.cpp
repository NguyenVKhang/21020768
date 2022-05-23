#include "player.h"

player::player(){
    frame = 0;
    width_frame = 0;
    height_frame = 0;
    current_clip = &frameClips[0][0];
    animationPlayer = DOWN;
}

player::~player(){

}

bool player::loadImg(string path, SDL_Renderer* render){
    bool ret = baseObject::loadImg(path, render);
    if(ret == true){
        width_frame = mRect.w/3;
        height_frame = mRect.h/4;
    }
    return ret;
}

void player::setClips(){
    if(width_frame > 0 && height_frame > 0){
        frameClips[0][0].x = 0;
        frameClips[0][0].y = 0;
        frameClips[0][0].w = width_frame;
        frameClips[0][0].h = height_frame;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                frameClips[i][j].x = j*width_frame;
                frameClips[i][j].y = i*height_frame;
                frameClips[i][j].w = width_frame;
                frameClips[i][j].h = height_frame;
            }
        }
    }
}

void player::showPlayer(SDL_Renderer* render, animation animationOj){
    if(animationOj == NONE) frame = 0;
    else frame ++;
    if(frame >= 3) frame = 0;
    else if(frame < 0) frame = 2;
    switch (animationOj)
    {
    case UP:
        current_clip = &frameClips[3][frame];
        animationPlayer = UP;
        break;
    case DOWN:
        current_clip = &frameClips[0][frame];
        animationPlayer = DOWN;
        break;
    case LEFT:
        current_clip = &frameClips[1][frame];
        animationPlayer = LEFT;
        break;
    case RIGHT:
        current_clip = &frameClips[2][frame];
        animationPlayer = RIGHT;
        break;
    case NONE:
        current_clip = &frameClips[animationPlayer][0];
    }
    SDL_RenderCopy(render, mObject, current_clip, &mRect);
}

void player::handelInput(SDL_Event event, SDL_Renderer* render){
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym)
        {
            case SDLK_RIGHT:
                input_type.right_ = 1;
                break;
            case SDLK_UP:
                input_type.up_ = 1;
                break;
            case SDLK_DOWN:
                input_type.down_ = 1;
                break;
            case SDLK_LEFT:
                input_type.left_ = 1;
                break;
        }
    }
    else if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym)
        {
            case SDLK_RIGHT:
                input_type.right_ = 0;
                break;
            case SDLK_UP:
                input_type.up_ = 0;
                break;
            case SDLK_DOWN:
                input_type.down_ = 0;
                break;
            case SDLK_LEFT:
                input_type.left_ = 0;
                break;
        }
    }
}

void player::setPos(double x, double y){
    posX = x;
    posY = y;
}

void player::setCurrentClips(){
    current_clip = &frameClips[0][0];
}

void player::free(){
    if(mObject == NULL){
        SDL_DestroyTexture(mObject);
        mObject = NULL;
        mRect = {0, 0, 0, 0};
    }
}