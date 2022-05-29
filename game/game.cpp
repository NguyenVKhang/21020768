#include "game.h"


void showMenuWin(SDL_Renderer* renderer, int step, int time, status& statusGame, bool& quit, int& level, TTF_Font* font){
    SDL_Event event;
    baseObject screenWin;
    baseObject backLevel;
    stringstream text;
    SDL_Color colorText = {104, 75, 56, 255};
    text << "Level: " << level << ". Step: " << step <<". Time: " << time <<"s.";
    baseObject textGame;
    textGame.loadFromRenderedText(text.str().c_str(), colorText, renderer, font);
    textGame.setRect((SCREEN_WIDTH-680)/2, 400, 680, 140);
    backLevel.loadImg("img/left-arrow.png", renderer);
    backLevel.setRect(276, 660, 200, 200);
    baseObject nextLevel;
    nextLevel.loadImg("img/right-arrow.png", renderer);
    nextLevel.setRect(836, 660, 200, 200);
    baseObject restartLevel;
    restartLevel.loadImg("img/restart.png", renderer);
    restartLevel.setRect(580, 800, 140, 140);
    baseObject menuGame;
    menuGame.loadImg("img/home.png", renderer);
    menuGame.setRect(580, 550, 140, 140);
    Effect soundWin;
    soundWin.loadEffect("sound/winGame.wav");
    screenWin.loadImg("img/winGame.png", renderer);
    screenWin.setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    soundWin.play(true);
    bool gameWin = true;
    while(gameWin){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
                gameWin = false;
            }
            if(backLevel.handleEventMouse(event)){
                backLevel.setRect(266, 650, 220, 220);
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    if(level <= 1) level = 1;
                    else level --;
                    gameWin = false;
                }
            }
            else backLevel.setRect(276, 660, 200, 200);
            if(nextLevel.handleEventMouse(event)){
                nextLevel.setRect(826, 650, 220, 220);
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    if(level >= TOTAL_LV) level = TOTAL_LV;
                    else level ++;
                    gameWin = false;
                }
            }
            else nextLevel.setRect(836, 660, 200, 200);
            if(restartLevel.handleEventMouse(event)){
                restartLevel.setRect(570, 790, 160, 160);
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    gameWin = false;
                }
            }
            else restartLevel.setRect(580, 800, 140, 140);
            if(menuGame.handleEventMouse(event)){
                menuGame.setRect(570, 540, 160, 160);
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    statusGame = MENU;
                    gameWin = false;
                }
            }
            else menuGame.setRect(580, 550, 140, 140);
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_RIGHT){
                    if(level >= TOTAL_LV) level = 1;
                    else level ++;
                    gameWin = false;
                }
                else if(event.key.keysym.sym == SDLK_LEFT){
                    if(level <= 1) level = TOTAL_LV;
                    else level --;
                    gameWin = false;
                }
                if(event.key.keysym.sym == SDLK_UP){
                    statusGame = MENU;
                    gameWin = false;
                }
                if(event.key.keysym.sym == SDLK_DOWN){
                    gameWin = false;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer); 
        screenWin.render(renderer);
        backLevel.render(renderer);
        nextLevel.render(renderer);
        restartLevel.render(renderer);
        menuGame.render(renderer);
        textGame.render(renderer);
        SDL_RenderPresent(renderer);
    }
}

void specsGame::loadSpecsGame(int level){
    stringstream linkSetting;
    linkSetting << "settingMap/"<<level <<".txt";
    ifstream fileSetting(linkSetting.str().c_str());
    fileSetting >> isPass;
    fileSetting >> stepMin;
    fileSetting >> timeMin;
}


void gameLoops(SDL_Renderer* renderer, SDL_Event &event, status& statusGame, bool& quit, int& level, TTF_Font* font){
    int step = 0;
    Uint32 time = 0;
    time = SDL_GetTicks();
    SDL_Color text_color = {104, 75, 56, 255};
    specsGame specs_game;
    specs_game.loadSpecsGame(level);
    stringstream link;
    ObjectGame margin;
    loadImgMargin(margin, renderer, level, font, step, specs_game);
    link << "level/" << level << ".txt";
    bool isWin = false;
    gameMap mapGame;
    animation animationOj = NONE;
    Music footStepEffect;
    footStepEffect.loadMusic("sound/playerMove.wav");
    mapGame.loadMap(link.str());
    mapGame.loadTiles(renderer);
    bool gameRun = true;
    while(gameRun){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                gameRun = false;
                quit = true;
            }
            margin.handleMouseMargin(event, statusGame, quit, level, font, gameRun, step, mapGame);
            mapGame.handelInput(event, renderer, step, animationOj);
        }
        if(margin.step != step){
            margin.step = step;
            stringstream text_step;
            text_step << "Step: " << step << "    ";
            margin.textStep.free();
            if(!margin.textStep.loadFromRenderedText(text_step.str().c_str(), text_color, renderer, font)){
                cout << "load anh textStep khong thanh cong " << SDL_GetError();
            }
            else margin.textStep.setRect(1000, 120, 240, 60);
        }
        if(margin.time != (SDL_GetTicks() - time)/1000){
            stringstream text_time;
            margin.time = (SDL_GetTicks() - time)/1000;
            margin.textTime.free();
            text_time << "Time: "<< margin.time <<"s";
            if(!margin.textTime.loadFromRenderedText(text_time.str().c_str(), text_color, renderer, font)){
                cout << "load anh textTime khong thanh cong " << SDL_GetError();
            }
            else margin.textTime.setRect(1000, 200, 240, 60);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        if(animationOj != NONE) footStepEffect.play(true);
        else  footStepEffect.stop();
        mapGame.drawMap(renderer, isWin, step, animationOj);
        showGameMarginBot(margin, renderer);
        showGameMarginTop(margin, renderer, font, level, step, time);
        SDL_RenderPresent(renderer);
        if(isWin && animationOj == NONE){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            if(animationOj != NONE) footStepEffect.play(true);
            else  footStepEffect.stop();
            mapGame.drawMap(renderer, isWin, step, animationOj);
            showGameMarginBot(margin, renderer);
            showGameMarginTop(margin, renderer, font, level, step, time);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);
            gameRun = false;
        } 
    }
    footStepEffect.free();
    mapGame.free();
    if(isWin){
        handleSecsMap(specs_game, (SDL_GetTicks() - time)/1000, step, level);
        showMenuWin(renderer, step, (SDL_GetTicks()-time)/1000 , statusGame, quit, level, font);
    }
}

void loadImgMargin(ObjectGame& margin, SDL_Renderer* render, int level, TTF_Font* font, int step, specsGame specs_game){
    SDL_Color text_color = {104, 75, 56, 255};
    margin.step = 0;
    margin.time = 0;
    if(!margin.home.loadImg("img/home.png", render)){
        cout << "load margin home khong thanh cong" << SDL_GetError();
    }
    else margin.home.setRect(1070, 700, 100, 100);
    if(!margin.restart.loadImg("img/restart.png", render)){
        cout << "load anh restart khong thanh cong " << SDL_GetError();
    }
    else margin.restart.setRect(1140, 840, 100, 100);
    if(!margin.undo.loadImg("img/undo.png", render)){
        cout << "load anh undo khong thanh cong " << SDL_GetError();
    }
    else margin.undo.setRect(1000, 840, 100, 100);
    stringstream text_level;
    text_level << "Level: " << level;
    if(!margin.textLevel.loadFromRenderedText(text_level.str().c_str(), text_color, render, font)){
        cout << "load anh textLevel khong thanh cong " << SDL_GetError();
    }
    else margin.textLevel.setRect(1000, 40, 240, 60);
    stringstream bestResult;
    bestResult << "BEST RESUL";
    if(!margin.bestResult.loadFromRenderedText(bestResult.str().c_str(), text_color,render, font)){
        cout << "load anh bestResult khong thanh cong " << SDL_GetError();
    }
    else margin.bestResult.setRect(1000, 300, 240, 60);
    stringstream textSpecsTime;
    textSpecsTime << "Time: "<<specs_game.timeMin <<"s";
    if(!margin.textTimeMin.loadFromRenderedText(textSpecsTime.str().c_str(), text_color, render, font)){
        cout << "load anh textTimeMin khong thanh cong " << SDL_GetError();
    }
    else margin.textTimeMin.setRect(1000, 460, 240, 60);
    stringstream textSpecsStep;
    textSpecsStep << "Step: " <<specs_game.stepMin ;
    if(!margin.textStepMin.loadFromRenderedText(textSpecsStep.str().c_str(), text_color, render, font)){
        cout << "load anh textStepMin khong thanh cong " << SDL_GetError();
    }
    else margin.textStepMin.setRect(1000, 380, 240, 60);
    stringstream text_step;
    text_step << "Step: " << step << "    ";
    margin.textStep.free();
    if(!margin.textStep.loadFromRenderedText(text_step.str().c_str(), text_color, render, font)){
        cout << "load anh textStep khong thanh cong " << SDL_GetError();
    }
    else margin.textStep.setRect(1000, 120, 240, 60);
    stringstream text_time;
    margin.textTime.free();
    text_time << "Time: 0s";
    if(!margin.textTime.loadFromRenderedText(text_time.str().c_str(), text_color, render, font)){
        cout << "load anh textTime khong thanh cong " << SDL_GetError();
    }
    else margin.textTime.setRect(1000, 200, 240, 60);
}

void showGameMarginBot(ObjectGame margin, SDL_Renderer* render){
    SDL_SetRenderDrawColor(render, 218, 165, 32, 255);
    SDL_Rect marginBackground = {960, 660, 320, 300};
    SDL_RenderFillRect(render, &marginBackground);
    margin.home.render(render);
    margin.undo.render(render);
    margin.restart.render(render);
}

void ObjectGame::handleMouseMargin(SDL_Event& event, status& statusGame, bool& quit, int& level, TTF_Font *font, bool &gameRun, int& step, gameMap& mapGame){
    if(home.handleEventMouse(event)){
        home.setRect(1060, 700, 120, 120);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            gameRun = false;
            statusGame = MENU;
        }
    }
    else home.setRect(1070, 700, 100, 100);
    if(undo.handleEventMouse(event)){
        undo.setRect(990, 830, 120, 120);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(step > 0) mapGame.go_back(step);
        }
    }
    else undo.setRect(1000, 840, 100, 100);
    if(restart.handleEventMouse(event)){
        restart.setRect(1130, 830, 120, 120);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            gameRun = false;
        }
    }
    else restart.setRect(1140, 840, 100, 100);
}

void showGameMarginTop(ObjectGame margin, SDL_Renderer* renderer, TTF_Font* font, int level, int step, Uint32 time){
    SDL_SetRenderDrawColor(renderer, 129, 154, 156, 255);
    SDL_Rect marginBackground = {960, 0, 320, 660};
    SDL_RenderFillRect(renderer, &marginBackground);
    margin.textLevel.render(renderer);  
    SDL_Color text_color = {104, 75, 56, 255};
    margin.textStep.render(renderer);
    margin.textLevel.render(renderer);  
    margin.textTime.render(renderer);
    SDL_SetRenderDrawColor(renderer, 218, 165, 32, 255);
    for(int i = 0; i < 5; i++){
        SDL_RenderDrawLine(renderer, 960, 280 + i, 1280, 280 + i );
    }
    margin.bestResult.render(renderer);
    margin.textTimeMin.render(renderer);
    margin.textStepMin.render(renderer);
    
}

void handleSecsMap(specsGame specs_game, int time, int step, int level){
    if(specs_game.timeMin > time || specs_game.isPass == false){
        ofstream outfile;
        stringstream path;
        path << "settingMap/"<<level << ".txt";
        outfile.open(path.str().c_str());
        outfile << '1' <<" ";
        outfile << step << " ";
        outfile << time;
        outfile.close();
    }
}
