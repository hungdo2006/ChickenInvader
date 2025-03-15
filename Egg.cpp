#include "Egg.h"
#include "Config.h"
#include <iostream>
using  namespace std;
Egg::Egg(int x, int y, SDL_Texture* texture,SDL_Texture* brokenTex) {
    mPosX = x;
    mPosY = y;
    eggTexture = texture;
    brokenTexture = brokenTex;
    isBroken = false;
    breakTime = 0;
    toBeRemoved = false;
    rectEgg = {mPosX, mPosY, 20, 25};
}

Egg::~Egg() {}

void Egg::update() {
    if (isBroken) {
        if (SDL_GetTicks() - breakTime > 500) {
            toBeRemoved = true;
        }
        return;
    }
    mPosY += mSpeed;
    rectEgg.y = mPosY;
}

void Egg::render(SDL_Renderer* renderer) {
    if (!eggTexture) {
    cout << "Egg texture is NULL!" << endl;
    }
     if (isBroken) {
       SDL_RenderCopy(renderer, brokenTexture, nullptr, &rectEgg);
    } else {
        SDL_RenderCopy(renderer, eggTexture, nullptr, &rectEgg);
    }
}
void Egg::onCollision() {
    isBroken = true;
    breakTime = SDL_GetTicks();
}
bool Egg::shouldRemove() {
    return toBeRemoved;
}

SDL_Rect Egg::getRect() {
    return rectEgg;
}

bool Egg::isOffScreen() {
    return mPosY > SCREEN_HEIGHT;
}
bool Egg::getBroken(){
    return isBroken;
}
