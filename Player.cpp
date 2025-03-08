#include "Player.h"
#include "Config.h"
#include "Game.h"
Player::Player()
{
    mPosX = 0;
    mPosY = 0;

	mColliderPlayer.w = Player_WIDTH;
	mColliderPlayer.h = Player_HEIGHT;

    mVelX = 0;
    mVelY = 0;
}

void Player::handleEvent( SDL_Event& e )
{
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
void Player::move()
{
    mPosX += mVelX;
	mColliderPlayer.x = mPosX;

    if( ( mPosX < 0 ) || ( mPosX + Player_WIDTH > SCREEN_WIDTH ))
    {
        mPosX -= mVelX;
		mColliderPlayer.x = mPosX;
    }


    mPosY += mVelY;
	mColliderPlayer.y = mPosY;

    if( ( mPosY < 0 ) || ( mPosY + Player_HEIGHT > SCREEN_HEIGHT ))
    {
        mPosY -= mVelY;
		mColliderPlayer.y = mPosY;
    }
}
void Player::render(SDL_Renderer* renderer)
{
	playerTexture.renderT( mPosX, mPosY,renderer);
}

