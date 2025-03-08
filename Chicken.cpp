#include "Chicken.h"
#include "Config.h"

Chicken::Chicken()
{
    mPosX = 0;
    mPosY = 0;

	mColliderChicken.w = Chicken_WIDTH;
	mColliderChicken.h = Chicken_HEIGHT;

    mVelX = 0;
    mVelY = 0;
}
Chicken::Chicken(int x , int y){
    mPosX = x;
    mPosY = y;

	mColliderChicken.w = Chicken_WIDTH;
	mColliderChicken.h = Chicken_HEIGHT;

    mVelX = 0;
    mVelY = 0;
}
void Chicken::render(SDL_Renderer* renderer)
{
	chickenTexture.renderT( mPosX, mPosY,renderer);
}
