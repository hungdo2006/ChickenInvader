#ifndef NORMAL_BULLET_H
#define NORMAL_BULLET_H

#include "Bullet.h"

class NormalBullet : public Bullet {
public:
    NormalBullet(int x, int y, SDL_Texture* tex) : Bullet(x, y, tex, -5) {}
};

#endif
