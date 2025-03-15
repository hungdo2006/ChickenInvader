#include "Bullet.h"
#include "Config.h"

Bullet::Bullet(int x, int y, SDL_Texture* tex, int moveSpeed) {
    mPosX = x;
    mPosY = y;
    mVelY = moveSpeed;
    rectBullet = {mPosX, mPosY, Bullet_WIDTH, Bullet_HEIGHT};
    texture = tex;
}

Bullet::~Bullet() {
}

void Bullet::update() {
    mPosY += mVelY;
    rectBullet.y = mPosY;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rectBullet);
}

bool Bullet::isOffScreen() const {
    return mPosY + rectBullet.h < 0;
}
int Bullet::getShootSpeed(){
    return shootSpeed;
}
SDL_Rect Bullet::getRect() const {
    return rectBullet;
}
