#include "menuGame.h"

void showMenu(SDL_Renderer* renderer, SDL_Event event, status& statusGame, int& level, bool& quit, TTF_Font* font){
    statusMenu status_menu = MAIN;
    bool music = true;
    Music musicGame;
    Effect selectionSound;
    musicGame.loadMusic("sound/musicGame.mp3");
    selectionSound.loadEffect("sound/selection.mp3");
    musicGame.play(true); 
    bool quitMenu = false;
    while(!quitMenu){
        switch(status_menu)
        {
            case MAIN:
                showMenuMain(renderer, status_menu, quit, quitMenu);
                break;
            case GUIDE:
                showGuide(renderer, quit, status_menu);
                break;
            case SELECT_LEVEL:
                showLevel(renderer, level, font, statusGame, status_menu, quitMenu, quit);
                break;
            case SETTING:
                clearSettingMap(renderer, quit, status_menu, font);
        }
        if(quit == true) quitMenu = true;
        if(statusGame == GAME_PLAY) quitMenu = true;
    }
    musicGame.free();
}

void showMenuMain(SDL_Renderer* renderer, statusMenu& statusMenu, bool& quit, bool& quitMenu){
    SDL_Event event;
    bool quitMainMenu = false;
    MenuGame menu;
    menu.loadMenu(renderer);
    while(!quitMainMenu){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            } 
            menu.renderInput(event, quit, quitMainMenu, statusMenu);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);      
        menu.menuGameRender(renderer);
        SDL_RenderPresent(renderer);
        if(quit == true) quitMainMenu = true;
    }
    menu.free();
}

void showLevel(SDL_Renderer* renderer, int& level, TTF_Font* font, status& statusGame, statusMenu& status_menu, bool& quitMenu, bool& quit){
    baseObject backgroundLevel;
    baseObject back;
    back.loadImg("img/back_button.png", renderer);
    back.setRect((SCREEN_WIDTH - 200)/2, 840, 200, 100);
    backgroundLevel.loadImg("img/select_level.png", renderer);
    vector<buttonLevel> levelButton;
    for(int i = 0; i < TOTAL_LV; i++){
        buttonLevel buttonTg;
        buttonTg.loadButtonLevel(renderer, i, font);
        levelButton.push_back(buttonTg);
    }
    SDL_Event event;
    bool quitShowLevel = false;
    while(!quitShowLevel){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            } 
            for(int i = 0; i < TOTAL_LV; i++){
                levelButton[i].handleInput(event, renderer, level, i, quit, statusGame);
            }
            if(quit == true){
                quitShowLevel = true;
            }
            if(statusGame == GAME_PLAY) quitShowLevel = true;
            if(back.handleEventMouse(event)){
                back.setRect((SCREEN_WIDTH - 200)/2 - 10, 840 - 10, 220, 120);
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    quitShowLevel = true;
                    status_menu = MAIN;
                }
            }
            else  back.setRect((SCREEN_WIDTH - 200)/2, 840, 200, 100);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer); 
        backgroundLevel.render(renderer);  
        back.render(renderer);   
        for(int i = 0; i < TOTAL_LV; i++){
            levelButton[i].renderButtonLevel(renderer);
        }
        SDL_RenderPresent(renderer);
    }
    for(int i = 0; i < TOTAL_LV; i++){
        levelButton[i].free();
    }
    backgroundLevel.free();
}

void MenuGame::loadMenu(SDL_Renderer* renderer){
    if(!backgroundMenu.loadImg("img/background.png", renderer)){
        cout << "load background menu khong thanh cong " << SDL_GetError() << endl;
    }
    else backgroundMenu.setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(!buttonPlay.loadImg("img/play_button.png", renderer)){
        cout << "load buttonPlay menu khong thanh cong " << SDL_GetError() << endl;
    }
    else buttonPlay.setRect((SCREEN_WIDTH - buttonPlay.getRect().w)/2, SCREEN_HEIGHT/3, buttonPlay.getRect().w, buttonPlay.getRect().h);
    if(!buttonGuide.loadImg("img/guide_button.png", renderer)){
        cout << "load buttonGuide menu khong thanh cong " << SDL_GetError() << endl;
    }
    else buttonGuide.setRect((SCREEN_WIDTH - buttonGuide.getRect().w)/2, SCREEN_HEIGHT/3 + 130, buttonGuide.getRect().w, buttonGuide.getRect().h);
    if(!buttonReset.loadImg("img/reset_button.png", renderer)){
        cout << "load buttonReset menu khong thanh cong " << SDL_GetError() << endl;
    }
    else buttonReset.setRect((SCREEN_WIDTH - buttonReset.getRect().w)/2, SCREEN_HEIGHT/3 + 260, buttonReset.getRect().w, buttonReset.getRect().h);
    if(!buttonQuit.loadImg("img/quit_button.png", renderer)){
        cout << "load buttonQuit menu khong thanh cong " << SDL_GetError() << endl;
    }
    else buttonQuit.setRect((SCREEN_WIDTH - buttonQuit.getRect().w)/2, SCREEN_HEIGHT/3 + 390, buttonQuit.getRect().w, buttonQuit.getRect().h);
}

void MenuGame::menuGameRender(SDL_Renderer* renderer){
    backgroundMenu.render(renderer);
    buttonPlay.render(renderer);
    buttonGuide.render(renderer);
    buttonReset.render(renderer);
    buttonQuit.render(renderer);
}

void MenuGame::renderInput(SDL_Event event, bool& quit, bool& quitMainMenu, statusMenu& status_menu){
    if(buttonPlay.handleEventMouse(event)){
        buttonPlay.setRect((SCREEN_WIDTH - 320)/2 - 10, SCREEN_HEIGHT/3 - 10 , 320 + 20, 96 + 20);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            status_menu = SELECT_LEVEL;
            quitMainMenu = true;
        }
    }
    else buttonPlay.setRect((SCREEN_WIDTH - 320)/2 , SCREEN_HEIGHT/3 , 320, 96);

    if(buttonGuide.handleEventMouse(event)){
        buttonGuide.setRect((SCREEN_WIDTH - 320)/2 - 10, SCREEN_HEIGHT/3 + 130 - 10 , 320 + 20, 96 + 20);
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            status_menu = GUIDE;
            quitMainMenu = true;
        } 
    }
    else buttonGuide.setRect((SCREEN_WIDTH - 320)/2 , SCREEN_HEIGHT/3 + 130 , 320, 96);

    if(buttonReset.handleEventMouse(event)){
        buttonReset.setRect((SCREEN_WIDTH - 320)/2 - 10, SCREEN_HEIGHT/3 - 10 + 260, 320 + 20, 96 + 20);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            status_menu = SETTING;
            quitMainMenu = true;
        }
    }
    else buttonReset.setRect((SCREEN_WIDTH - 320)/2 , SCREEN_HEIGHT/3 + 260, 320, 96);

    if(buttonQuit.handleEventMouse(event)){
        buttonQuit.setRect((SCREEN_WIDTH - 320)/2 - 10, SCREEN_HEIGHT/3 - 10 + 390, 320 + 20, 96 + 20);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            quit = true;

        }
    }
    else buttonQuit.setRect((SCREEN_WIDTH - 320)/2 , SCREEN_HEIGHT/3 + 390, 320, 96);

}
void MenuGame::free(){
    backgroundMenu.free();
    buttonGuide.free();
    buttonPlay.free();
    buttonQuit.free();
    buttonReset.free();
}

void showGuide(SDL_Renderer* renderer, bool& quit, statusMenu& statusMenu){
    baseObject backgroundGuide;
    backgroundGuide.loadImg("img/guide_background.png", renderer);
    SDL_Event event;
    baseObject back;
    back.loadImg("img/back_button.png", renderer);
    back.setRect((SCREEN_WIDTH - 200)/2, 20, 200, 100);
    bool quitGuide = false;
    while(!quitGuide){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
                quitGuide = true;
            } 
            if(event.key.keysym.sym == SDLK_RETURN){
                quitGuide = true;
                statusMenu = MAIN;
            }
            if(back.handleEventMouse(event)){
                back.setRect((SCREEN_WIDTH - 200)/2 - 10, 20 - 10, 220, 120);
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    quitGuide = true;
                    statusMenu = MAIN;
                }
            }
            else  back.setRect((SCREEN_WIDTH - 200)/2, 20, 200, 100);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);      
        backgroundGuide.render(renderer);
        back.render(renderer);
        SDL_RenderPresent(renderer);
    }
}

void buttonLevel::loadButtonLevel(SDL_Renderer* renderer, int level, TTF_Font* font){
    stringstream path ;
    path << "settingMap/"<<level + 1 << ".txt";
    ifstream file(path.str().c_str());
    bool isPass;
    file >> isPass;
    if(isPass == false) backgroundButton.loadImg("img/level_button.png", renderer);
    else backgroundButton.loadImg("img/button.png", renderer);
    stringstream text;
    text << level+1;
    SDL_Color color = {104, 75, 56, 255};
    textLevel.loadFromRenderedText(text.str().c_str(), color, renderer, font);
    int x = level%6;
    int y = level/6;
    backgroundButton.setRect(160 + x*180, 384 + y*150, backgroundButton.getRect().w, backgroundButton.getRect().h);
    textLevel.setRect(160 + x*180, 384 + y*150, backgroundButton.getRect().w, backgroundButton.getRect().h);
}

void buttonLevel::renderButtonLevel(SDL_Renderer* renderer){
    backgroundButton.render(renderer);
    textLevel.render(renderer);
}

void buttonLevel::free(){
    backgroundButton.free();
    textLevel.free();
}

void buttonLevel::handleInput(SDL_Event event, SDL_Renderer* renderer, int& level, int index, bool& quit, status& statusGame){
    int x = index%6;
    int y = index/6;
    if(backgroundButton.handleEventMouse(event)){
        backgroundButton.setRect(160 + x*180 - 10, 384 + y*150 - 10, 96 + 20, 96 + 20);
        textLevel.setRect(160 + x*180 - 10, 384 + y*150 - 10, 96 + 20, 96 + 20);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            level = index + 1;
            statusGame = GAME_PLAY;
        }
    }
    else{
        backgroundButton.setRect(160 + x*180, 384 + y*150, 96, 96);
        textLevel.setRect(160 + x*180, 384 + y*150, 96, 96);
    } 

}

void clearSettingMap(SDL_Renderer* renderer, bool& quit, statusMenu& statusMenu, TTF_Font* font){
    baseObject backgroundSetting;
    backgroundSetting.loadImg("img/background.png", renderer);
    SDL_Event event;
    SDL_Color colorText = {104, 75, 56, 255};
    bool quitSetting = false;
    stringstream text;
    text << "You definitely want to reset the game?";
    baseObject textGame;
    textGame.loadFromRenderedText(text.str().c_str(), colorText, renderer, font);
    textGame.setRect(((SCREEN_WIDTH) - 680)/2, SCREEN_HEIGHT/2 - 100, 720, 100);
    stringstream text2;
    text2 << "Press Y to confirm or N to return to menu";
    baseObject text2Game;
    text2Game.loadFromRenderedText(text2.str().c_str(), colorText, renderer, font);
    text2Game.setRect(((SCREEN_WIDTH) - 680)/2, SCREEN_HEIGHT/2, 720, 100);
    bool confirm = false;
    while(!quitSetting){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
                quitSetting = true;
            } 
            if(event.key.keysym.sym == SDLK_y){
                confirm = true;
                quitSetting = true;
                statusMenu = MAIN;
            }
            else if(event.key.keysym.sym == SDLK_n){
                confirm = false;
                quitSetting = true;
                statusMenu = MAIN;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);   
        backgroundSetting.render(renderer);
        textGame.render(renderer);   
        text2Game.render(renderer);
        SDL_RenderPresent(renderer);
    }
    if(confirm){
        for(int i = 1; i <= TOTAL_LV; i++){
            stringstream path;
            path << "settingMap/" << i <<".txt";
            ofstream file;
            file.open(path.str().c_str());
            file << "0 0 0";
            file.close();
        }
    }
}