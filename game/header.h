#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
const int GAME_WIDTH = 950;
const int GAME_HEIGHT = 950;


#define MAX_MAP_X 20
#define MAX_MAP_Y 20

#define TOTAL_LV 18
enum status{
    MENU,
    GAME_PLAY
};

struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
};

enum animation{
    DOWN = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    NONE = 4
};

enum tile{
    WALL = 1,
    FLOOR = 2,
    PLAYER = 3,
    BOX = 4,
    GOAL = 5,
    BOX_WIN = 6
};

