#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <bits/stdc++.h>
#include "Player.h"
#include "Chicken.h"
#include "Bullet.h"
#include "LaserBullet.h"
#include "Utils.h"
#include "Random.h"
#include "Config.h"
#include "Background.h"

using namespace std;

struct Buff {
    int x, y;
    int fallSpeed = 2;
    Uint32 spawnTime;
    SDL_Texture* texture;
    bool isHeal;
};

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
    void restartGame();
    void spawnChickens(int num);
    void shoot(bool isLaser);
    void toggleBulletType();
    void toggleAutoShoot();
    void updateBullets();
    void renderBullets(SDL_Renderer* renderer);
    void setGameState(GameState state);
    void handleCollisions();
    SDL_Texture* loadTexture(const string& filePath);
    void spawnBuff();

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running ;
    GameState gameState;
    Player* player;
    vector<Chicken*> chickens;
    vector<Bullet*> bullets;
    Background* background;
    bool isLaser = false;
    int shootSpeed = BASE_SHOOT_SPEED;
    Uint32 lastShotTime = 0;
    bool autoShoot = false;
    SDL_Texture* chickenTexture;
    SDL_Texture* eggTexture;
    SDL_Texture* laserTexture;
    SDL_Texture* eggBrokenTexture;
    SDL_Texture* menuTexture;
    SDL_Texture* startButtonTexture;
    SDL_Rect startButtonRect;
    SDL_Texture* gameOverTexture;
    SDL_Texture* restartButtonTexture;
    SDL_Rect restartButtonRect;
    SDL_Texture* victoryTexture;
    vector<Buff> buffs;
    SDL_Texture* healBuffTexture;
    SDL_Texture* fireRateBuffTexture;
    Uint32 fireRateBuffStartTime = 0;
    bool fireRateBuffActive = false;
    double fireRateMultiplier = 1.0;
};

#endif
