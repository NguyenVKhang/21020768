#pragma once

#include "header.h"
#include "baseObject.h"
#include "player.h"



struct map{
    int arrMap[MAX_MAP_X][MAX_MAP_Y];
    string fileName;
    int mapX;
    int mapY;
    int sizeX;
    int sizeY;
    int posPlayerX;
    int posPlayerY;
    int posBoxMoveX;
    int posBoxMoveY;
    player player;
};



class gameMap
{
    public:
        gameMap(){;}
        ~gameMap(){;}
        void loadMap(string path);
        void loadTiles(SDL_Renderer* render);
        void drawMap(SDL_Renderer* render, bool& isWin, int& step, animation& animationOj);
        void handelInput(SDL_Event event, SDL_Renderer* render, int& step, animation& animationOj);
        void go_back(int& step);
        void free();
    private:
        vector <map> game_map;
        baseObject wall;
        baseObject box;
        baseObject box_win;
        baseObject floor;
        baseObject goal;
        player mainPlayer;
        bool boxMove;
};