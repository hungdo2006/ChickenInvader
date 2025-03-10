#include <bits/stdc++.h>
#include "Player.h"
#include "Game.h"
#include "Config.h"

Player::Player(Game* game,int x, int y){
    mPosX = x;
    mPosY = y;
    mVelX = 0;
    mVelY = 0;
    rectPlayer = {mPosX, mPosY, 50, 50};
    texture = game->loadTexture("assets/textures/player.jpg");
    if (!texture) {
        cout << "Fail to load player image!" << IMG_GetError() << endl;
    }
}
Player::~Player(){
   if (texture) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    }
}
void Player::handleInput( SDL_Event& e, Game* game )
{
     bool isLaser = false;
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Player_VEL; break;
            case SDLK_DOWN: mVelY += Player_VEL; break;
            case SDLK_LEFT: mVelX -= Player_VEL; break;
            case SDLK_RIGHT: mVelX += Player_VEL; break;
            case SDLK_SPACE: game->shoot(isLaser); break;
            case SDLK_l: isLaser = !isLaser; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Player_VEL; break;
            case SDLK_DOWN: mVelY -= Player_VEL; break;
            case SDLK_LEFT: mVelX += Player_VEL; break;
            case SDLK_RIGHT: mVelX -= Player_VEL; break;
        }
    }
}
void Player::update()
{
    mPosX += mVelX;
     mPosY += mVelY;

    if( ( mPosX < 0 ) || ( mPosX + Player_WIDTH > SCREEN_WIDTH ))
    {
        mPosX -= mVelX;
    }
    if( ( mPosY < 0 ) || ( mPosY + Player_HEIGHT > SCREEN_HEIGHT ))
    {
        mPosY -= mVelY;
    }

    rectPlayer.x = mPosX;
    rectPlayer.y = mPosY;
}
void Player::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rectPlayer);
}
SDL_Rect Player::getRect() const {
    return rectPlayer;
}

