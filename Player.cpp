#include <bits/stdc++.h>
#include "Player.h"
#include "Game.h"

Player::Player(Game* game,int x, int y){
    health = maxHealth;
    mPosX = x;
    mPosY = y;
    mVelX = 0;
    mVelY = 0;
    rectPlayer = {mPosX, mPosY, Player_WIDTH, Player_HEIGHT};
    texture = game->loadTexture("assets/textures/player.png");
    if (!texture) {
        cout << "Fail to load player image!" << IMG_GetError() << endl;
    }
}
Player::~Player(){
}

bool Player::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        return true;
    }
    return false;
}
void Player::heal(int healing){
    health += healing;
    if(health >= maxHealth){
        health = maxHealth;
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
    SDL_Rect healthBarBg = {mPosX, mPosY - 10,rectPlayer.w, Player_HEALTH_BAR_WIDTH};
    SDL_Rect healthBar = {mPosX, mPosY - 10, rectPlayer.w*health / maxHealth, Player_HEALTH_BAR_WIDTH};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &healthBarBg);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &healthBar);

    SDL_RenderCopy(renderer, texture, nullptr, &rectPlayer);
}
SDL_Rect Player::getRect() const {
    return rectPlayer;
}
void Player::reset() {
    mPosX = SCREEN_WIDTH/2;
    mPosY = SCREEN_HEIGHT/2  + 50;
    health = maxHealth;
}



