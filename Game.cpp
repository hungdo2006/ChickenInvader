#include <bits/stdc++.h>
#include "Game.h"
#include "Config.h"
using namespace std;

Game::Game(){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    bool running = false;
}
Game::~Game() {
    close();
}
bool Game::init(){
    bool success = true;
    gameState = MENU;
    if(SDL_Init((SDL_INIT_VIDEO | SDL_INIT_AUDIO)< 0)){
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

                int mixerFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
                if(!Mix_Init(mixerFlags)){
                    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError()<< endl;
                    success = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    cout << "SDL_mixer could not open audio! Mix_Error: " << Mix_GetError() << endl;
                    success = false;
                }

                if(TTF_Init() == -1){
                    cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
                    success = false;
                }else{
                    font = TTF_OpenFont("font/font2.ttf", FONT_SIZE);
                    if (!font) {
                            cout << "Failed to load font: " << TTF_GetError() << endl;
                    }
                }

            }
        }
    }
    menuTexture = loadTexture("assets/textures/background2.jpg");

    startButtonRect = {482, 250, 317, 100};
    tutorialButtonRect = {482, 350, 317, 100};
    highScoreButtonRect = {482, 450, 317, 100};
    exitButtonRect = {482, 550, 317, 100};
    restartButtonRect = {482, 600, 317, 100};
    returnButtonRect = {SCREEN_WIDTH - 50,0,50,50};

    startButtonTexture = loadTexture("assets/textures/start1.png");
    tutorialTexture = loadTexture("assets/textures/tutorialTexture.png");
    tutorialButtonTexture = loadTexture("assets/textures/tutorial1.png");
    exitButtonTexture = loadTexture("assets/textures/exit1.png");
    returnButtonTexture = loadTexture("assets/textures/return.png");
    highScoreTexture = loadTexture("assets/textures/highScore1.jpg");
    highScoreButtonTexture = loadTexture("assets/textures/highScore.png");

    gameOverTexture = loadTexture("assets/textures/game_over2.jpg");
    restartButtonTexture = loadTexture("assets/textures/restart1.png");
    victoryTexture = loadTexture("assets/textures/victory1.jpg");
    healBuffTexture = loadTexture("assets/textures/heal_buff.png");
    fireRateBuffTexture = loadTexture("assets/textures/speedbuff1.png");
    background = new Background(this, "assets/textures/space2.png", 2);
    chickenTexture = loadTexture("assets/textures/chicken1.png");
    bossTexture = loadTexture("assets/textures/boss.png");
    laserTexture = loadTexture("assets/textures/laser.png");
    eggTexture = loadTexture("assets/textures/egg.png");
    eggBrokenTexture = loadTexture("assets/textures/egg_broken.png");

    running = true;
    loadHighScore();
    spawnChickens(NUM_CHICKENS);
    player = new Player(this, (SCREEN_WIDTH-Player_WIDTH)/2, SCREEN_HEIGHT/2  + 200);
    if (!SoundManager::loadSounds()) {
    cout << "Failed to load audio!" << endl;
    }
    SoundManager::playBackgroundMusic();

    return success;
}
SDL_Texture* Game::loadTexture(const std::string& filePath){
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        cout << "Failed to load texture!" << filePath << " - " << IMG_GetError() << endl;
    }
    return texture;
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
void Game::handleEvents(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }
        if (gameState == MENU && e.type == SDL_MOUSEBUTTONDOWN) {
            int x = e.button.x, y = e.button.y;
            if (x >= startButtonRect.x && x <= startButtonRect.x + startButtonRect.w && y >= startButtonRect.y && y <= startButtonRect.y + startButtonRect.h) {
                SoundManager::playClickSound();
                restartGame();
                gameState = PLAYING;
            }else if(x >= tutorialButtonRect.x && x <= tutorialButtonRect.x + tutorialButtonRect.w && y >= tutorialButtonRect.y && y <= tutorialButtonRect.y + tutorialButtonRect.h){
                SoundManager::playClickSound();
                gameState = TUTORIAL;
            }else if(x >= highScoreButtonRect.x && x <= highScoreButtonRect.x + highScoreButtonRect.w && y >= highScoreButtonRect.y && y <= highScoreButtonRect.y + highScoreButtonRect.h){
                SoundManager::playClickSound();
                gameState = HIGH_SCORE;
            }else if(x >= exitButtonRect.x && x <= exitButtonRect.x + exitButtonRect.w && y >= exitButtonRect.y && y <= exitButtonRect.y + exitButtonRect.h){
                SoundManager::playClickSound();
                running = false;
            }
        }
        if (gameState == GAME_OVER && e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x, y = e.button.y;
        if (x >= restartButtonRect.x && x <= restartButtonRect.x + restartButtonRect.w &&
            y >= restartButtonRect.y && y <= restartButtonRect.y + restartButtonRect.h) {
            SoundManager::playClickSound();
            restartGame();
            }else if(x >= returnButtonRect.x && x <= returnButtonRect.x + returnButtonRect.w &&
            y >= returnButtonRect.y && y <= returnButtonRect.y + returnButtonRect.h){
                SoundManager::playClickSound();
                gameState = MENU;
            }
        }
        if (gameState == STATE_VICTORY && e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x, y = e.button.y;
        if (x >= restartButtonRect.x && x <= restartButtonRect.x + restartButtonRect.w &&
            y >= restartButtonRect.y && y <= restartButtonRect.y + restartButtonRect.h) {
            SoundManager::playClickSound();
            restartGame();
            }else if(x >= returnButtonRect.x && x <= returnButtonRect.x + returnButtonRect.w &&
            y >= returnButtonRect.y && y <= returnButtonRect.y + returnButtonRect.h){
                SoundManager::playClickSound();
                gameState = MENU;
            }
        }
        if(gameState ==  TUTORIAL && e.type == SDL_MOUSEBUTTONDOWN){
        int x = e.button.x, y = e.button.y;
        if (x >= returnButtonRect.x && x <= returnButtonRect.x + returnButtonRect.w &&
            y >= returnButtonRect.y && y <= returnButtonRect.y + returnButtonRect.h) {
                SoundManager::playClickSound();
                gameState = MENU;
            }
        }
        if(gameState ==  HIGH_SCORE && e.type == SDL_MOUSEBUTTONDOWN){
        int x = e.button.x, y = e.button.y;
        if (x >= returnButtonRect.x && x <= returnButtonRect.x + returnButtonRect.w &&
            y >= returnButtonRect.y && y <= returnButtonRect.y + returnButtonRect.h) {
                SoundManager::playClickSound();
                gameState = MENU;
            }
        }
        player->handleInput(e,this);
        if (e.type == SDL_KEYDOWN&& e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_SPACE:
                    shoot();
                    break;
                case SDLK_t:
                    toggleAutoShoot();
                    break;
            }
        }
    }
}
void Game::update(){
    if (gameState == GAME_OVER){
        if (score > highScore) {
                highScore = score;
                saveHighScore();
            }
    }
     if (gameState == PLAYING && waveCount < maxWaves && chickens.empty()) {
        spawnChickens(NUM_CHICKENS + waveCount*5);
        waveCount++;
    }else if(gameState == PLAYING && waveCount == maxWaves && chickens.empty()){
        gameState = STATE_BOSS;
        chickens.clear();
        Chicken* boss = new Chicken(SCREEN_WIDTH / 2 - 75, 50,bossTexture,eggTexture,eggBrokenTexture,bossTexture);
        boss->setSize(150, 150);
        boss->setHealth(CHICKEN_BOSS_HEALTH);
        boss->setBoss();
        boss->setBossVel(3,3);
        chickens.push_back(boss);
    }
    if (gameState == STATE_BOSS &&chickens.empty()) {
        gameState = STATE_VICTORY;
        if (score > highScore) {
                highScore = score;
                saveHighScore();
            }
    }


    if (gameState == PLAYING || gameState == STATE_BOSS){

    background->update();
    player->update();
   for (size_t i = 0; i < chickens.size(); i++) {
        chickens[i]->update();
        for (size_t j = 0; j < chickens[i]->getEggs().size(); j++) {
                Egg* egg = chickens[i]->getEggs()[j];
            if (checkCollision(player->getRect(), egg->getRect())) {
                 if (!egg->getBroken()) {
                    egg->onCollision();
                    SoundManager::playEggSound();
                    if (score >= REMOVE_SCORE_PER_EGG) {
                            score -= REMOVE_SCORE_PER_EGG;
                    } else {
                            score = 0;
                    }
                    if (player->takeDamage(Player_TAKE_DAMAGE)) {
                        cout << "Game Over!" << endl;
                        gameState = GAME_OVER;
                    }
                }
            }
            if (egg->shouldRemove()){
                    chickens[i]->removeEgg(j);
                    j--;
            }
        }
        if (chickens[i]->getIsDead()) {
            SoundManager::playExplosionSound();
            score += SCORE_PER_CHICKEN;
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
            gameState = GAME_OVER;
        }
    }
    Uint32 currentTime = SDL_GetTicks();

    if (autoShoot && currentTime - lastShotTime >= shootSpeed) {
        shoot();
        lastShotTime = currentTime;
    }

    updateBullets();
    spawnBuff();
    for (size_t i = 0; i < buffs.size(); i++) {
        buffs[i].y += buffs[i].fallSpeed;
        if (buffs[i].y > SCREEN_HEIGHT) {
            buffs.erase(buffs.begin() + i);
            i--;
            continue;
        }

        if (SDL_GetTicks() - buffs[i].spawnTime > TIME_SPAWN_BUFF) {
            buffs.erase(buffs.begin() + i);
            i--;
            continue;
        }

        if (checkCollision(player->getRect(), {buffs[i].x, buffs[i].y, Buff_WIDTH, Buff_HEIGHT})) {
                if (buffs[i].isHeal) {
                        player->heal(Player_HEALING);
                } else {
                        fireRateBuffActive = true;
                        fireRateBuffStartTime = SDL_GetTicks();
                        fireRateMultiplier += 0.25;
                        if (fireRateMultiplier > MAX_FIRE_RATE_MULTIPLIER) {
                                    fireRateMultiplier = MAX_FIRE_RATE_MULTIPLIER;
                        }
                        shootSpeed = BASE_SHOOT_SPEED / fireRateMultiplier;
                }
                buffs.erase(buffs.begin() + i);
                i--;
        }
        if (fireRateBuffActive && SDL_GetTicks() - fireRateBuffStartTime >= Buff_DURATION) {
                fireRateBuffActive = false;
                shootSpeed = BASE_SHOOT_SPEED;
                fireRateMultiplier = 1.0;
        }
    }

    }
}
void Game::render() {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

     if (gameState == MENU) {
            SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
            SDL_RenderCopy(renderer, startButtonTexture, NULL, &startButtonRect);
            SDL_RenderCopy(renderer,tutorialButtonTexture,NULL,&tutorialButtonRect);
            SDL_RenderCopy(renderer,highScoreButtonTexture,NULL,&highScoreButtonRect);
            SDL_RenderCopy(renderer,exitButtonTexture,NULL,&exitButtonRect);
    } else if (gameState == PLAYING || gameState == STATE_BOSS) {
            background->render(renderer);
            renderScore(10,10,SCREEN_WIDTH - 450,10);
            for (auto* chicken : chickens){
                chicken->render(renderer);
            }

            player->render(renderer);
            renderBullets(renderer);
            for (auto& buff : buffs) {
                SDL_Rect dst = {buff.x, buff.y, Buff_WIDTH, Buff_HEIGHT};
                SDL_RenderCopy(renderer, buff.texture, NULL, &dst);
            }
    }else if (gameState == GAME_OVER) {
        SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
        SDL_RenderCopy(renderer, restartButtonTexture, NULL, &restartButtonRect);
        SDL_RenderCopy(renderer,returnButtonTexture,NULL,&returnButtonRect);
        renderScore(SCREEN_WIDTH/2 - 200 , SCREEN_HEIGHT-400, SCREEN_WIDTH/2 - 200 , SCREEN_HEIGHT-300);
    }else if (gameState == STATE_VICTORY) {
        SDL_RenderCopy(renderer, victoryTexture, NULL, NULL);
        SDL_RenderCopy(renderer, restartButtonTexture, NULL, &restartButtonRect);
        SDL_RenderCopy(renderer,returnButtonTexture,NULL,&returnButtonRect);
        renderScore(SCREEN_WIDTH/2 - 200 , SCREEN_HEIGHT-400, SCREEN_WIDTH/2 - 200 , SCREEN_HEIGHT-300);
    }else if(gameState == TUTORIAL){
        SDL_RenderCopy(renderer,tutorialTexture,NULL,NULL);
        SDL_RenderCopy(renderer,returnButtonTexture,NULL,&returnButtonRect);
    }else if(gameState == HIGH_SCORE){
        SDL_RenderCopy(renderer,highScoreTexture,NULL,NULL);
        renderScoreMenu();
        SDL_RenderCopy(renderer,returnButtonTexture,NULL,&returnButtonRect);
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
    SDL_DestroyTexture(highScoreTexture);
    SDL_DestroyTexture(highScoreButtonTexture);
    SDL_DestroyTexture(returnButtonTexture);
    SDL_DestroyTexture(tutorialTexture);
    SDL_DestroyTexture(tutorialButtonTexture);
    SDL_DestroyTexture(exitButtonTexture);
    SDL_DestroyTexture(restartButtonTexture);
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(startButtonTexture);
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(victoryTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(bossTexture);
    SDL_DestroyTexture(eggTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    IMG_Quit();
    TTF_CloseFont(font);
    SoundManager::clean();
}

void Game::spawnChickens(int NUM_CHICKENS) {
    chickens.clear();
    for (int i = 0; i < NUM_CHICKENS; i++) {
        int x = Random(0,SCREEN_WIDTH-Chicken_WIDTH);
        int y = Random(0,SCREEN_HEIGHT/2 - Chicken_HEIGHT);
        chickens.push_back(new Chicken(x, y,chickenTexture,eggTexture,eggBrokenTexture,bossTexture));
    }
}
void Game::shoot() {
    if (player) {
        int playerX = player->getRect().x + (Player_WIDTH - Bullet_WIDTH)/2;
        int playerY = player->getRect().y;
        bullets.push_back(new LaserBullet(playerX, playerY, laserTexture));
    }
    SoundManager::playShootSound();
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

                chickens[j]->takeDamage(Chicken_TAKE_DAMAGE);

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
void Game::restartGame() {
    player->reset();
    chickens.clear();
    spawnChickens(NUM_CHICKENS);
    fireRateBuffActive = false;
    shootSpeed = BASE_SHOOT_SPEED;
    waveCount = 1;
    score = 0;
    autoShoot = false;
    for (size_t i = 0; i < bullets.size(); i++) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
    }
    gameState = PLAYING;
}
void Game::spawnBuff() {
    if (Random(0, 100) < SPAWN_RATE) {
        Buff buff;
        buff.x = Random(0, SCREEN_WIDTH - 40);
        buff.y = Random(50, SCREEN_HEIGHT / 2);
        buff.isHeal = Random(0,1);
        buff.texture = buff.isHeal ? healBuffTexture : fireRateBuffTexture;
        buff.spawnTime = SDL_GetTicks();
        buffs.push_back(buff);
    }
}
void Game::renderScore(int x , int y , int x1 , int y1){
    SDL_Color white = {255, 255, 255};

    string scoreText = "Score: " + to_string(score);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    string highScoreText = "High Score: " + to_string(highScore);
    SDL_Surface* highScoresurface = TTF_RenderText_Solid(font, highScoreText.c_str(), white);
    SDL_Texture* highScoretexture = SDL_CreateTextureFromSurface(renderer, highScoresurface);
    SDL_Rect highTextRect = {x1, y1, highScoresurface->w, highScoresurface->h};
    SDL_RenderCopy(renderer, highScoretexture, NULL, &highTextRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(highScoresurface);
    SDL_DestroyTexture(highScoretexture);
}
void Game::renderScoreMenu(){
    SDL_Color white = {255, 255, 255};

    string highScoreTextMenu = "Your High Score: " + to_string(highScore);
    SDL_Surface* highScoreMenusurface = TTF_RenderText_Solid(font, highScoreTextMenu.c_str(), white);
    SDL_Texture* highScoreMenutexture = SDL_CreateTextureFromSurface(renderer, highScoreMenusurface);
    SDL_Rect highTextMenuRect = {(SCREEN_WIDTH - highScoreMenusurface->w)/2,(SCREEN_HEIGHT - highScoreMenusurface->h)/2, highScoreMenusurface->w, highScoreMenusurface->h};
    SDL_RenderCopy(renderer, highScoreMenutexture, NULL, &highTextMenuRect);

    SDL_FreeSurface(highScoreMenusurface);
    SDL_DestroyTexture(highScoreMenutexture);
}
void Game::loadHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
        cout << "High Score Loaded: " << highScore << endl;
    } else {
        cout << "Failed to load highscore.txt" << endl;
    }
}
void Game::saveHighScore() {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
        cout << "High Score Saved: " << highScore << endl;
    } else {
        cout << "Failed to save highscore.txt" << endl;
    }
}

