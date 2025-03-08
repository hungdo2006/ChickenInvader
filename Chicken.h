#ifndef CHICKEN_H
#define CHICKEN_H
#include <SDL.h>

class Chicken
{
    public:
		Chicken();
		Chicken(int x, int y);
		void handleEvent( SDL_Event& e );
		void move();
		void render(SDL_Renderer* renderer);
    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		SDL_Rect mColliderChicken;
};
#endif
