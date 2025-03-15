#include "Egg.h"
#include "Config.h"
#include <iostream>
using  namespace std;
Egg::Egg(int x, int y, SDL_Texture* texture) {
    mPosX = x;
    mPosY = y;
    eggTexture = texture;
    rectEgg = {mPosX, mPosY, 20, 25};
}

Egg::~Egg() {}

void Egg::update() {
    mPosY += mSpeed;
    rectEgg.y = mPosY;
}

void Egg::render(SDL_Renderer* renderer) {
    if (!eggTexture) {
    cout << "Egg texture is NULL!" << endl;
    }
    SDL_RenderCopy(renderer, eggTexture, nullptr, &rectEgg);
}

SDL_Rect Egg::getRect() {
    return rectEgg;
}

bool Egg::isOffScreen() {
    return mPosY > SCREEN_HEIGHT;
}
