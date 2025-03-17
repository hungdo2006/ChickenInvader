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
    gameState = MENU;
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
    menuTexture = loadTexture("assets/textures/menu.jpg");
    startButtonTexture = loadTexture("assets/textures/start_button.png");
    startButtonRect = {200, 300, 200, 100};
    gameOverTexture = loadTexture("assets/textures/game_over.jpg");
    restartButtonTexture = loadTexture("assets/textures/restart_button.jpg");
    restartButtonRect = {300, 450, 200, 100};
    victoryTexture = loadTexture("assets/textures/victory.jpg");

    player = new Player(this, SCREEN_WIDTH/2, SCREEN_HEIGHT/2  + 50);
    background = new Background(this, "assets/textures/background.png", 2);
    chickenTexture = loadTexture("assets/textures/chicken.png");
    eggTexture = loadTexture("assets/textures/egg.png");
    eggBrokenTexture = loadTexture("assets/textures/egg_broken.png");
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
        if (gameState == MENU && e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x, y = e.button.y;
        if (x >= startButtonRect.x && x <= startButtonRect.x + startButtonRect.w &&
            y >= startButtonRect.y && y <= startButtonRect.y + startButtonRect.h) {
            gameState = PLAYING;
            }
        }
        if (gameState == GAME_OVER && e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x, y = e.button.y;
        if (x >= restartButtonRect.x && x <= restartButtonRect.x + restartButtonRect.w &&
            y >= restartButtonRect.y && y <= restartButtonRect.y + restartButtonRect.h) {
            restartGame();
            }
        }
        if (gameState == STATE_VICTORY && e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x, y = e.button.y;
        if (x >= restartButtonRect.x && x <= restartButtonRect.x + restartButtonRect.w &&
            y >= restartButtonRect.y && y <= restartButtonRect.y + restartButtonRect.h) {
            restartGame();
            }
        }
        player->handleInput(e,this);
        if (e.type == SDL_KEYDOWN&& e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_SPACE:
                    shoot(isLaser);
                    break;
                case SDLK_t:
                    toggleAutoShoot();
                    break;
                case SDLK_b:
                    toggleBulletType();
                    break;
            }
        }
    }
}
void Game::update(){
    if (gameState == GAME_OVER) return;
    if (chickens.empty()) {
    gameState = STATE_VICTORY;
    return;
    }
    background->update();
    player->update();
   for (size_t i = 0; i < chickens.size(); i++) {
        chickens[i]->update();
        for (size_t j = 0; j < chickens[i]->getEggs().size(); j++) {
                Egg* egg = chickens[i]->getEggs()[j];
            if (checkCollision(player->getRect(), egg->getRect())) {
                 if (!egg->getBroken()) {
                    egg->onCollision();
                    if (player->takeDamage(10)) {
                        cout << "Game Over!" << endl;
                        setGameState(GAME_OVER);
                    }
                }
            }
            if (egg->shouldRemove()){
                    chickens[i]->removeEgg(j);
                    j--;
            }
        }
        if (chickens[i]->getIsDead()) {
            vector<Egg*>& eggs = chickens[i]->getEggs();
            for (size_t j = 0; j < eggs.size(); j++) {
                delete eggs[j];
            }
            eggs.clear();
            delete chickens[i];
            chickens.erase(chickens.begin() + i);
            i--;
        }
    }

     for (auto chicken : chickens) {
        if (checkCollision(player->getRect(), chicken->getRect())) {
            cout << "Game Over!" << endl;
            setGameState(GAME_OVER);
        }
    }
    Uint32 currentTime = SDL_GetTicks();

    if (autoShoot && currentTime - lastShotTime >= shootSpeed) {
        shoot(isLaser);
        lastShotTime = currentTime;
    }

    updateBullets();
}
void Game::render() {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

     if (gameState == MENU) {
            SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
            SDL_RenderCopy(renderer, startButtonTexture, NULL, &startButtonRect);
    } else if (gameState == PLAYING) {
            background->render(renderer);

            for (auto* chicken : chickens){
                chicken->render(renderer);
            }

            player->render(renderer);
            renderBullets(renderer);
    }else if (gameState == GAME_OVER) {
        SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
        SDL_RenderCopy(renderer, restartButtonTexture, NULL, &restartButtonRect);
    }else if (gameState == STATE_VICTORY) {
        SDL_RenderCopy(renderer, victoryTexture, NULL, NULL);
        SDL_RenderCopy(renderer, restartButtonTexture, NULL, &restartButtonRect);
    }

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

    delete background;
    SDL_DestroyTexture(restartButtonTexture);
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(startButtonTexture);
     SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(victoryTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(eggTexture);
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
        chickens.push_back(new Chicken(this, x, y,chickenTexture,eggTexture,eggBrokenTexture));
    }
}
void Game::shoot(bool isLaser) {
    if (player) {
        SDL_Texture* bulletTexture = loadTexture("assets/textures/bullet.png");
        SDL_Texture* laserTexture = loadTexture("assets/textures/laser.png");

        int playerX = player->getRect().x + (Player_WIDTH - Bullet_WIDTH)/2;
        int playerY = player->getRect().y;

        if (isLaser) {
            bullets.push_back(new LaserBullet(playerX, playerY, laserTexture));
        } else {
            bullets.push_back(new NormalBullet(playerX, playerY, bulletTexture));
        }
    }
}
void Game::toggleBulletType() {
    isLaser = !isLaser;
    shootSpeed = isLaser ? 100 : 300;
    cout << "Switched bullet type: " << (isLaser ? "Laser" : "Normal") << endl;
}
void Game::toggleAutoShoot() {
    autoShoot = !autoShoot;
     cout << "Switched shoot type: " << (autoShoot ? "AutoShoot" : "NormalShoot") << endl;
}
void Game::updateBullets() {
    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i]->update();

        if (bullets[i]->isOffScreen()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
            continue;
        }

        for (int j = 0; j < chickens.size(); j++) {
            if (checkCollision(bullets[i]->getRect(), chickens[j]->getRect())) {

                chickens[j]->takeDamage(25);

                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                i--;

                break;
            }
        }
    }
}
void Game::renderBullets(SDL_Renderer* renderer) {
    for (auto bullet : bullets) {
        bullet->render(renderer);
    }
}
void Game::setGameState(GameState state) {
    gameState = state;
}
void Game::restartGame() {
    player->reset();
    chickens.clear();
    spawnChickens(NUM_CHICKENS);
    gameState = PLAYING;
}

