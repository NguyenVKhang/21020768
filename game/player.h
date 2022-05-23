#pragma once 

#include "header.h"
#include "baseObject.h"

class player : public baseObject{
    public:
        player();
        ~player();
        void showPlayer(SDL_Renderer* render, animation animationOj);
        void handelInput(SDL_Event event, SDL_Renderer* render);
        void setClips();
        bool loadImg(string path, SDL_Renderer* render);
        void setPos(double x, double y);
        double getPosX(){return posX;}
        double getPosY(){return posY;}
        void setCurrentClips();
        void free();
    private:
        SDL_Rect frameClips[4][3];
        animation playerStatus;
        Input input_type;
        int frame;
        int width_frame;
        int height_frame;
        SDL_Rect* current_clip;
        double posX;
        double posY;
        animation animationPlayer;
};

