#include "LaserBullet.h"
#include "Config.h"
LaserBullet::LaserBullet(int x, int y, SDL_Texture* tex) : Bullet(x, y, tex, LASER_BULLET_SPEED) {}
void LaserBullet::update() {
    mPosY += mVelY;
    rectBullet.y = mPosY;
}
