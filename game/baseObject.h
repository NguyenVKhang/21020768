#pragma once
#include "header.h"

class baseObject{
public:
    baseObject();
    ~baseObject();
    void setRect(const int &x, const int &y, const int &w, const int &h) {mRect.x = x; mRect.y = y; mRect.w = w; mRect.h = h;}
    SDL_Rect getRect() const {return mRect;}
    SDL_Texture* getObject() const {return mObject;}
    virtual bool loadImg(string path, SDL_Renderer* renderer);
    #if defined(SDL_TTF_MAJOR_VERSION)
	bool loadFromRenderedText(string textureText, SDL_Color textColor , SDL_Renderer* renderer, TTF_Font* font);
	#endif
    bool handleEventMouse(SDL_Event event);
    void render(SDL_Renderer* renderer, SDL_Rect* clip = NULL);
    void free();
protected:
    SDL_Texture* mObject;
    SDL_Rect mRect;
};