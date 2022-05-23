#include "baseObject.h"

baseObject::baseObject(){
    mObject = NULL;
    mRect = {0, 0, 0, 0};
}

baseObject::~baseObject(){
    free();
}

bool baseObject::loadImg(string path, SDL_Renderer* renderer){
    free();
    SDL_Surface* mSurface = IMG_Load(path.c_str());
    SDL_Texture* newTexture;
    if(mSurface == NULL){
        cout << "load surface khong thanh cong" << SDL_GetError() << '\n';
    }
    else{
        SDL_SetColorKey(mSurface, SDL_TRUE, SDL_MapRGB(mSurface -> format, 255, 255, 255));
        newTexture = SDL_CreateTextureFromSurface(renderer, mSurface);
        if(newTexture == NULL){
            cout << "load texture tu surface khong thanh cong" << SDL_GetError() << endl;
        }
        else{
            mRect.w = mSurface -> w;
            mRect.h = mSurface ->h;
        }
        SDL_FreeSurface(mSurface);
    }
    mObject = newTexture;
    return mObject != NULL;
}

void baseObject::render(SDL_Renderer* renderer, SDL_Rect* clip){
    SDL_Rect renderQuad = {mRect.x, mRect.y, mRect.w, mRect.h};
    SDL_RenderCopy(renderer, mObject, clip, &renderQuad);
}

void baseObject::free(){
    if(mObject == NULL){
        SDL_DestroyTexture(mObject);
        mObject = NULL;
        mRect = {0, 0, 0, 0};
    }
}


#if defined(SDL_TTF_MAJOR_VERSION)
bool baseObject::loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font  )
{
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
        mObject = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( mObject == NULL )
		{
			cout << "Unable to create texture from rendered text! SDL Error: " <<  TTF_GetError() << endl;
		}
		else
		{
			mRect.w = textSurface->w;
			mRect.h = textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}
	else
	{
		cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() ;
	}
	return mObject != NULL;
}
#endif
	
bool baseObject::handleEventMouse(SDL_Event event){
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(mRect.x > x || mRect.y > y || mRect.x + mRect.w < x || mRect.y + mRect.h < y) return false;
    else return true;
}