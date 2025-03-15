#include "Chicken.h"
#include "Config.h"
#include "Game.h"
#include "Random.h"
#include <iostream>
#include <vector>

Chicken::Chicken(Game* game, int x, int y, SDL_Texture* texture,  SDL_Texture* eggTex,SDL_Texture* eggBrokenTex){
    health = maxHealth;
    mPosX = x;
    mPosY = y;

    mVelX = Random(-3, 3);
    mVelY = Random(1, 3);

    rectChicken = {mPosX, mPosY, 50, 50};

   chickenTexture = texture;
   eggTexture = eggTex;
   eggBrokenTexture = eggBrokenTex;
    eggTimer = Random(100,300);
    if (!chickenTexture&&eggTexture) {
        cout << "Fail to load chicken image!" << IMG_GetError() << endl;
    }
}

void Chicken::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        isDead = true;
    }
}

bool Chicken::getIsDead(){
    return isDead;
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

    eggTimer--;
    if (eggTimer <= 0) {
        layEgg(eggTexture,eggBrokenTexture);
        eggTimer = rand() % 200 + 100;
    }
    for (size_t i = 0; i < eggs.size(); i++) {
        eggs[i]->update();
        if (eggs[i]->isOffScreen()) {
            eggs.erase(eggs.begin() + i);
            i--;
        }
    }
}

void Chicken::layEgg(SDL_Texture* eggTexture,SDL_Texture* eggBrokenTex) {
     eggs.push_back(new Egg(mPosX + 10, mPosY + 50, eggTexture,eggBrokenTex));
}

void Chicken::render(SDL_Renderer* renderer)
{
    SDL_Rect healthBar = {mPosX, mPosY - 10, rectChicken.w*health / maxHealth, 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &healthBar);
    SDL_RenderCopy(renderer, chickenTexture, nullptr, &rectChicken);
    for (Egg* egg : eggs) {
        egg->render(renderer);
    }
}
SDL_Rect Chicken::getRect() const {
    return rectChicken;
}

void Chicken::removeEgg(int index) {
    if (index >= 0 && index < eggs.size()) {
        delete eggs[index];
        eggs.erase(eggs.begin() + index);
    }
}

vector<Egg*>& Chicken::getEggs() {
    return eggs;
}
Chicken::~Chicken(){
    for (Egg* egg : eggs) {
        delete egg;
    }
    eggs.clear();
}
