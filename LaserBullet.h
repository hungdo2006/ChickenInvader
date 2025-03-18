#ifndef LASER_BULLET_H
#define LASER_BULLET_H
#include "Bullet.h"

class LaserBullet : public Bullet {
public:
     LaserBullet(int x, int y, SDL_Texture* tex) : Bullet(x, y, tex, LASER_BULLET_SPEED) {}
};

#endif
