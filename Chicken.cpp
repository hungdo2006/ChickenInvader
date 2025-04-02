#include "Chicken.h"
#include "Game.h"
#include "Random.h"
#include <iostream>
#include <vector>

Chicken::Chicken( int x, int y, SDL_Texture* texture,  SDL_Texture* eggTex,SDL_Texture* eggBrokenTex, SDL_Texture* boss){
    health = maxHealth;
    mPosX = x;
    mPosY = y;

    mVelX = Random(-3, 3);
    mVelY = Random(1, 3);

    rectChicken = {mPosX, mPosY, Chicken_WIDTH, Chicken_HEIGHT};

    chickenTexture = texture;
    bossTexture = boss;
    eggTexture = eggTex;
    eggBrokenTexture = eggBrokenTex;
    eggTimer = ((isBoss) ? 50 : Random(100,300));
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
            if (isBoss) {
                    layEgg(eggTexture,eggBrokenTexture);
                    eggTimer = 50;
            } else {
                    layEgg(eggTexture,eggBrokenTexture);
                    eggTimer = Random(100,300);
            }
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
     if (isBoss) {
            int eggLocation[3] = {0, 75 ,150};
            for (int i = 0; i < 3; i++) {
                Egg* newEgg = new Egg(mPosX + eggLocation[i], mPosY + Chicken_HEIGHT, eggTexture, eggBrokenTex);
                eggs.push_back(newEgg);
            }
    } else {
     eggs.push_back(new Egg(mPosX + (Chicken_WIDTH/2), mPosY + Chicken_HEIGHT, eggTexture, eggBrokenTex));
    }
}

void Chicken::render(SDL_Renderer* renderer)
{
    if (maxHealth > 100){
            int barWidth = 1000;
            int barHeight = 10;
            int x =  (SCREEN_WIDTH - barWidth) / 2;
            int y = 50;
            double healthRatio = (double)health /CHICKEN_BOSS_HEALTH;
            int healthWidth = (int)(barWidth * healthRatio);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect healthBar = {x, y, healthWidth, barHeight};
            SDL_RenderFillRect(renderer, &healthBar);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect border = {x, y, barWidth, barHeight};
            SDL_RenderDrawRect(renderer, &border);
            SDL_RenderCopy(renderer, bossTexture, nullptr, &rectChicken);
    }else{
    SDL_Rect healthBar = {mPosX, mPosY - 10, rectChicken.w*health / maxHealth, Chicken_HEALTH_BAR_WIDTH};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &healthBar);
    SDL_RenderCopy(renderer, chickenTexture, nullptr, &rectChicken);
    }
    for (Egg* egg : eggs) {
        egg->render(renderer);
    }
}
void Chicken::renderBoss(SDL_Renderer* renderer){

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
int Chicken::getHealth(){
    return health;
}
void Chicken::setSize(int x , int y){
    rectChicken.w = x;
    rectChicken.h = y;
}
void Chicken::setHealth(int health){
    maxHealth = health;
    this->health = health;
}
void Chicken::setBoss(){
    isBoss = true;
}
void Chicken::setBossVel(int x , int y){
    mVelX = x;
    mVelY = y;
}
