#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <bits/stdc++.h>
#include "Player.h"
#include "Chicken.h"
#include "Bullet.h"
#include "Utils.h"
#include "Config.h"

using namespace std;
LTexture chickenTexture;
LTexture playerTexture;
class Game {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running ;

    Player player;
    vector<Chicken> chickens;

    bool loadMedia();

    Game();
    ~Game();

    bool init();
    void handleEvents();
    void update();
    void render();
    void close();

    void spawnChicken();
    void spawnBullet();

    void handleCollisions();
};

#endif
