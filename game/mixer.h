#pragma once
#include "header.h"


class Music{
    public:
        Music(){music == NULL;}
        ~Music(){;}
        void loadMusic(string path);
        void free();
        void play(bool isMusic);
        void stop();
    private:
        Mix_Music* music;
};

class Effect{
    public:
        Effect(){effect == NULL;}
        ~Effect(){;}
        void loadEffect(string path);
        void free();
        void play(bool isMusic);
        void stop();
    private:
        Mix_Chunk* effect;
};