#ifndef LASER_BULLET_H
#define LASER_BULLET_H

#include "Bullet.h"

class LaserBullet : public Bullet {
public:
    LaserBullet(int x, int y, SDL_Texture* tex);
    void update() override;
};

#endif
