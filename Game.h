#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <bits/stdc++.h>
#include "Player.h"
#include "Chicken.h"
#include "Bullet.h"
#include "NormalBullet.h"
#include "LaserBullet.h"
#include "Utils.h"
#include "Config.h"
#include "Background.h"

using namespace std;
class Game {
public:

    Game();
    ~Game();

    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    void close();
    bool isRunning();

    void spawnChickens(int num);
    void shoot(bool isLaser);
    void toggleBulletType();
    void toggleAutoShoot();
    void updateBullets();
    void renderBullets(SDL_Renderer* renderer);

    void handleCollisions();
    SDL_Texture* loadTexture(const string& filePath);

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running ;
    Player* player;
    vector<Chicken*> chickens;
    vector<Bullet*> bullets;
    Background* background;
    bool isLaser = false;
    int shootSpeed = 300;
    Uint32 lastShotTime = 0;
    bool autoShoot = false;
    SDL_Texture* chickenTexture;
    SDL_Texture* eggTexture;
};

#endif
