#include "Game.h"
#include "Utils.h"
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

    running = true;

    spawnChicken();

    return success;
}
bool Game::loadMedia(){
    bool success = true;
    if(!playerTexture.loadFromFile("assets/textures/player.jpg",renderer)){
        cout <<  "Failed to load player image!" << endl;
		success = false;
    }
    if(!chickenTexture.loadFromFile("assets/textures/chicken.png",renderer)){
        cout <<  "Failed to load chicken image!" << endl;
		success = false;
    }
    return success;
}
void Game::render() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player.render(renderer);

    for (size_t i = 0; i < chickens.size(); i++){
    chickens[i].render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::close() {
    playerTexture.free();
    chickenTexture.free();

      chickens.clear();


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    IMG_Quit();
}
void Game::spawnChicken() {
        Chicken chicken(Random(0, 800), Random(0, 200));
        chickens.push_back(chicken);
}

