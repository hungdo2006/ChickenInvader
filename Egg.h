#ifndef EGG_H
#define EGG_H

#include <SDL.h>
class Chicken;
class Egg {
public:
    Egg(int x, int y, SDL_Texture* texture);
    ~Egg();

    void update();
    void render(SDL_Renderer* renderer);

    SDL_Rect getRect();
    bool isOffScreen();

private:
    int mPosX, mPosY;
    int mSpeed = 3;
    SDL_Texture* eggTexture;
    SDL_Rect rectEgg;

};

#endif
