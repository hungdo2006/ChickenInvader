#include "Chicken.h"
#include "Config.h"
#include "Game.h"
#include <iostream>

Chicken::Chicken(Game* game, int x, int y){
    mPosX = x;
    mPosY = y;
     mVelX = 0;
    mVelY = 0;
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
    rectChicken.y += Chicken_VEL;
}
void Chicken::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rectChicken);
}
SDL_Rect Chicken::getRect() const {
    return rectChicken;
}
