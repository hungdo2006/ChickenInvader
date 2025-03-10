#include "Chicken.h"
#include "Config.h"
#include "Game.h"
#include "Random.h"
#include <iostream>

Chicken::Chicken(Game* game, int x, int y){
    mPosX = x;
    mPosY = y;

    mVelX = Random(-3, 3);
    mVelY = Random(1, 3);

    rectChicken = {mPosX, mPosY, 50, 50};

    texture = game->loadTexture("assets/textures/chicken.png");
    if (!texture) {
        cout << "Fail to load chicken image!" << IMG_GetError() << endl;
    }
}
Chicken::~Chicken() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
void Chicken::update() {
    mPosX += mVelX;
    mPosY += mVelY;
    if( ( mPosX < 0 ) || ( mPosX + Chicken_WIDTH > SCREEN_WIDTH ))
    {
        mVelX = -mVelX;
    }
    if( ( mPosY < 0 ) || ( mPosY + Chicken_HEIGHT > SCREEN_HEIGHT/2 ))
    {
        mVelY = -mVelY;
    }
    rectChicken.x = mPosX;
    rectChicken.y = mPosY;
}
void Chicken::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rectChicken);
}
SDL_Rect Chicken::getRect() const {
    return rectChicken;
}
