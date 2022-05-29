#pragma once

#include "header.h"
#include "baseObject.h"
#include "gameMap.h"
#include "player.h"
#include "mixer.h"

struct ObjectGame{
    int step;
    int time;
    baseObject home;
    baseObject restart;
    baseObject undo;
    baseObject textLevel;
    baseObject textTime;
    baseObject textStep;
    baseObject bestResult;
    baseObject textStepMin;
    baseObject textTimeMin;
    void handleMouseMargin(SDL_Event& event, status& statusGame, bool& quit, int& level, TTF_Font *font, bool &gameRun, int& step, gameMap& mapGame);
};
static baseObject gBackground;

struct specsGame{
    bool isPass;
    int stepMin;
    int timeMin;
    void loadSpecsGame(int level);
};

void gameLoops(SDL_Renderer* renderer, SDL_Event& event, status& statusGame, bool& quit, int& level, TTF_Font* font);
void showMenuWin(SDL_Renderer* renderer,  int step, int time, status& statusGame, bool& quit, int& level, TTF_Font* font);
void showGameMarginBot(ObjectGame margin ,SDL_Renderer* render);
void loadImgMargin(ObjectGame& margin, SDL_Renderer* renderer, int level, TTF_Font* font, int step, specsGame specs_game);
void showGameMarginTop(ObjectGame margin, SDL_Renderer* renderer, TTF_Font* font, int level, int step, Uint32 time);
void handleSecsMap(specsGame specs_game, int time, int step, int level);
