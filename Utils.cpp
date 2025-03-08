#include <cstdlib>
#include <ctime>
#include <string>
#include "Utils.h"

int Random(int min, int max) {
   bool seeded = false;
  if (!seeded) {
    srand(time(0));
    seeded = true;
  }
  return (rand() % (max - min + 1)) + min;
}
bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {

    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    if (bottomA <= topB) {
        return false;
    }
    if (topA >= bottomB) {
        return false;
    }
    if (rightA <= leftB) {
        return false;
    }
    if (leftA >= rightB) {
        return false;
    }
    return true;
}
LTexture::LTexture(){
    mTexture = NULL;
    width = 0;
    height = 0;
}
LTexture::~LTexture(){
    free();
}
void LTexture::free(){
    if(mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        width = 0;
        height = 0;
    }
}
bool LTexture::loadFromFile(string path,SDL_Renderer* renderer){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* image = IMG_Load(path.c_str());
    if(image == NULL){
        cout << "Unable to load image " << IMG_GetError() << endl;
    }else{
        SDL_SetColorKey(image,SDL_TRUE,SDL_MapRGB(image->format,0,255,255));
        newTexture = SDL_CreateTextureFromSurface(renderer, image);
        if(newTexture == NULL){
            cout << "Unable to create texture " << SDL_GetError() << endl;
        }else{
            width = image->w;
            height = image->h;
        }
    }
    mTexture = newTexture;
    SDL_FreeSurface(image);
    return mTexture != NULL;
}
/*
bool LTexture::loadFromText(string text, SDL_Color textColor){
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if(textSurface == NULL){
        cout << "Unable to render text " << TTF_GetError() << endl;
    }else{
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(mTexture == NULL){
            cout << "Unable to create texture " << SDL_GetError() << endl;
        }else{
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return mTexture != NULL;
}
*/
void LTexture::renderT(int x, int y,SDL_Renderer* renderer){
    SDL_Rect renderQuad = {x,y,40,40};
   SDL_RenderCopy(renderer,mTexture,NULL,&renderQuad);
}
void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b){
    SDL_SetTextureColorMod(mTexture, r, g, b);
}
void LTexture::setBlendMode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(mTexture, blending);
}
void LTexture::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod(mTexture, alpha);
}
int LTexture::getHeight(){
    return height;
}
int LTexture::getWidth(){
    return width;
}

