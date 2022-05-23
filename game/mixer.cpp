#include "mixer.h"

void Music::loadMusic(string path){
    music = Mix_LoadMUS(path.c_str());
    if(music == NULL){
        cout << "load music khong thanh cong " << Mix_GetError();
    }
}

void Music::free(){
    if(music != NULL){
        Mix_FreeMusic(music);
        music == NULL;
    }
}

void Music::play(bool isMusic){
    if(isMusic){
        Mix_PlayMusic(music, -1);
    }
}

void Music::stop(){
    Mix_PauseMusic();
}

void Effect::loadEffect(string path){
    effect = Mix_LoadWAV(path.c_str());
    if(effect == NULL){
        cout << "load effect khong thanh cong " << Mix_GetError();
    }
}

void Effect::free(){
    if(effect != NULL){
        Mix_FreeChunk(effect);
        effect == NULL;
    }
}

void Effect::play(bool isMusic){
    if(isMusic){
        Mix_PlayChannel(-1, effect, 0);
    }
}

void Effect::stop(){
    Mix_HaltMusic();
}