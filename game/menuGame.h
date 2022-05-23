#pragma once

#include "header.h"
#include "baseObject.h"
#include "mixer.h"

enum statusMenu{
    MAIN,
    SELECT_LEVEL,
    GUIDE,
    SETTING
};

struct MenuGame
{
    baseObject backgroundMenu;
    baseObject buttonPlay;
    baseObject buttonQuit;
    baseObject buttonReset;
    baseObject buttonGuide;
    void loadMenu(SDL_Renderer* renderer);
    void menuGameRender(SDL_Renderer* renderer);
    void renderInput(SDL_Event event, bool& quit, bool& quitMenu, statusMenu& status_menu);
    void free();
};

struct buttonLevel{
    baseObject backgroundButton;
    baseObject textLevel;
    
    void loadButtonLevel(SDL_Renderer* renderer, int level, TTF_Font* font);
    void renderButtonLevel(SDL_Renderer* renderer);
    void handleInput(SDL_Event event, SDL_Renderer* renderer, int& level, int index, bool& quit, status& statusGame);
    void free();
};

void showMenu(SDL_Renderer* renderer, SDL_Event event, status& statusGame, int& level, bool& quit, TTF_Font* font);

void showLevel(SDL_Renderer* renderer, int& level, TTF_Font* font, status& statusGame, statusMenu& statusMenu, bool& quitMenu, bool& quit);

void showMenuMain(SDL_Renderer* renderer, statusMenu& statusMenu, bool& quit, bool& quitMenu);

void loadSound();

void showGuide(SDL_Renderer* renderer, bool& quit, statusMenu& statusMenu);

void clearSettingMap(SDL_Renderer* renderer, bool& quit, statusMenu& statusMenu, TTF_Font* font);