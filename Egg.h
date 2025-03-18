#ifndef EGG_H
#define EGG_H
#include <SDL.h>
#include "Config.h"

class Chicken;
class Egg {
public:
    Egg(int x, int y, SDL_Texture* texture,SDL_Texture* brokenTex);
    ~Egg();
    void onCollision();
    void update();
    void render(SDL_Renderer* renderer);
    bool shouldRemove();
    SDL_Rect getRect();
    bool isOffScreen();
    bool getBroken();
private:
    int mPosX, mPosY;
    int mSpeed = Egg_SPEED;
    SDL_Texture* eggTexture;
    SDL_Rect rectEgg;
    SDL_Texture* brokenTexture;
    bool toBeRemoved;
    bool isBroken;
    Uint32 breakTime;
};

#endif
