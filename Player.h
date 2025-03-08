#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>

class Player
{
    public:
		Player();
		void handleEvent( SDL_Event& e );
		void move();
		void render(SDL_Renderer* renderer);
    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		SDL_Rect mColliderPlayer;
};

#endif
