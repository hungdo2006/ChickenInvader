#ifndef CHICKEN_H
#define CHICKEN_H
#include <SDL.h>
class Game;
class Chicken
{
    public:
		Chicken(Game* game, int x, int y);
		~Chicken();
		void update();
		void render(SDL_Renderer* renderer);
		SDL_Rect getRect() const;
    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		SDL_Rect rectChicken;
		SDL_Texture* texture;
};
#endif
