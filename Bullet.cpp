#include "Bullet.h"
#include "Config.h"
Bullet::Bullet(int x, int y, SDL_Texture* tex, int speed) {
    mPosX = x;
    mPosY = y;
    mVelY = speed;
    rectBullet = {mPosX, mPosY, Bullet_WIDTH, Bullet_HEIGHT};
    texture = tex;
}

Bullet::~Bullet() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
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

SDL_Rect Bullet::getRect() const {
    return rectBullet;
}
