#include "header.h"
#include "game.h"
#include "gameMap.h"
#include "player.h"
#include "menuGame.h"
#include "baseObject.h"


bool init(SDL_Window*& window, SDL_Renderer*& renderer){
    bool success = true;
    if(SDL_Init(SDL_INIT_EVERYTHING)  < 0){
        cout <<"init khong thanh cong" << SDL_GetError() << '\n';
        success = false;
    }
    else{
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            cout << "canh bao sethint khong thanh cong";
        }
        window = SDL_CreateWindow("sokoban", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            cout << "tao window khong thanh cong" << SDL_GetError() <<'\n';
            success = false;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == NULL){
                cout <<"tao render khong thanh cong" << SDL_GetError() << '\n';
                success = false;
            }
            else{
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                int flags = IMG_INIT_PNG;
                if(!IMG_Init(flags)&flags){
                    cout << "init png khong thanh cong" << IMG_GetError() <<'\n';
                    success = false;
                }
                if(TTF_Init() == -1){
                    cout << "init ttf khong thanh cong" << TTF_GetError();
                }
                if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
                    cout << "init mixer khong thanh cong " << Mix_GetError();
                    success = false;
                }
            }
        }
    }
    return success;
}




bool loadMedia(SDL_Window* window, SDL_Renderer* render){
    bool success = true;

    return success;
}

void close(SDL_Window*& window, SDL_Renderer*& renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}


int main(int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    if(!init(window, renderer)){
        cout << "init khong thanh cong" << SDL_GetError() << endl;
    }
    else {
        if(!loadMedia(window, renderer)){
            cout << "load media khong thanh cong " << SDL_GetError() << endl;
        }
        else{
            font = TTF_OpenFont("img/font.ttf", 96);
            status statusGame = MENU;
            SDL_Event event;
            bool quit = false;
            int level = 1;
            while(!quit){
                if(statusGame == MENU)  showMenu(renderer, event, statusGame, level, quit, font);
                else if(statusGame == GAME_PLAY) gameLoops(renderer, event, statusGame, quit, level, font);
            }

        }
    }
    close(window, renderer);
    return 0;
}
