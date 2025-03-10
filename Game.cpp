#include <bits/stdc++.h>
#include "Game.h"
#include "Config.h"
using namespace std;

Game::Game(){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    bool running = false;
}
Game::~Game() {
    close();
}
bool Game::init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO < 0)){
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }else{
        window = SDL_CreateWindow("Chicken Invaders",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window == NULL){
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }else{
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if(renderer == NULL){
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
               success = false;
            }else{
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                int imgFlags = IMG_INIT_PNG|IMG_INIT_JPG;
                if(!IMG_Init(imgFlags)){
                    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError()<< endl;
                    success = false;
                }
                /*
                if(TTF_Init() == -1){
                    cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
                    success = false;
                }
                */
            }
        }
    }
    player = new Player(this, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    running = true;

    spawnChickens(NUM_CHICKENS);

    return success;
}
SDL_Texture* Game::loadTexture(const std::string& filePath){
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        cout << "Failed to load texture!" << filePath << " - " << IMG_GetError() << endl;
    }
    return texture;
}
void Game::handleEvents(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }
        player->handleInput(e,this);
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE) {
            shoot(isLaser);
            }
            if (e.key.keysym.sym == SDLK_b) {
            toggleBulletType();
            }
        }
    }
}
void Game::update(){
    player->update();
    updateBullets();
    for (auto* chicken : chickens) {
        chicken->update();
    }
}
void Game::render() {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (auto* chicken : chickens){
        chicken->render(renderer);
    }

    player->render(renderer);
    renderBullets(renderer);

    SDL_RenderPresent(renderer);
}

void Game::close() {
      delete player;

    for (auto* chicken : chickens) {
        delete chicken;
    }
    chickens.clear();

    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    bullets.clear();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    IMG_Quit();
}
bool Game::isRunning(){
    return running;
}
void Game::run(){
    while (isRunning()) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}
void Game::spawnChickens(int NUM_CHICKENS) {
    chickens.clear();
    int startX = (SCREEN_WIDTH - (NUM_CHICKENS * CHICKEN_SPACING)) / 2;
    for (int i = 0; i < NUM_CHICKENS; i++) {
        int x = startX + i * CHICKEN_SPACING;
        int y = CHICKEN_Y_START;
        chickens.push_back(new Chicken(this, x, y));
    }
}
void Game::shoot(bool isLaser) {
    if (player) {
        SDL_Texture* bulletTexture = loadTexture("assets/textures/bullet.jpg");
        SDL_Texture* laserTexture = loadTexture("assets/textures/laser.jpg");

        int playerX = player->getRect().x + 20;
        int playerY = player->getRect().y;

        if (isLaser) {
            bullets.push_back(new LaserBullet(playerX, playerY, laserTexture));
        } else {
            bullets.push_back(new Bullet(playerX, playerY, bulletTexture, DEFAULT_BULLET_SPEED));
        }
    }
}
void Game::toggleBulletType() {
    isLaser = !isLaser;
    cout << "Switched bullet type: " << (isLaser ? "Laser" : "Normal") << endl;
}
void Game::updateBullets() {
    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i]->update();
        if (bullets[i]->isOffScreen()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}
void Game::renderBullets(SDL_Renderer* renderer) {
    for (auto bullet : bullets) {
        bullet->render(renderer);
    }
}
