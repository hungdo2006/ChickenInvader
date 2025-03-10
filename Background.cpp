#include "Background.h"
#include "Game.h"
#include <bits/stdc++.h>
using namespace std;
Background::Background(Game* game, const string& path, int speed) {
    texture = game->loadTexture(path);
    if (!texture) {
       cout << "Failed to load background: " << SDL_GetError() << endl;
    }
    this->speed = speed;
    bg1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    bg2 = {0, -SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
}

Background::~Background() {
    SDL_DestroyTexture(texture);
}

void Background::update() {
    bg1.y += speed;
    bg2.y += speed;

    if (bg1.y >= SCREEN_HEIGHT) {
        bg1.y = bg2.y - SCREEN_HEIGHT;
    }
    if (bg2.y >= SCREEN_HEIGHT) {
        bg2.y = bg1.y - SCREEN_HEIGHT;
    }
}

void Background::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &bg1);
    SDL_RenderCopy(renderer, texture, nullptr, &bg2);
}
