#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

class Bullet {

public:
     Bullet(int x, int y, SDL_Texture* tex, int speed);
    virtual ~Bullet();
    virtual void update();
    virtual void render(SDL_Renderer* renderer);
    virtual bool isOffScreen() const;
    SDL_Rect getRect() const;
protected:
    int mPosX, mPosY;
    int mVelY;
    SDL_Rect rectBullet;
    SDL_Texture* texture;
};

#endif
