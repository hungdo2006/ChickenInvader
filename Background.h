#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <bits/stdc++.h>
#include <SDL.h>
using namespace std;
class Game;
class Background {
public:
    Background(Game* game, const string& path, int speed);
    ~Background();

    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Texture* texture;
    SDL_Rect bg1, bg2;
    int speed;
};

#endif
