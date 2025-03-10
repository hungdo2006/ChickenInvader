#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
class Game;
class Player
{
    public:
		Player(Game* game,int x, int y);
		~Player();
		void handleInput( SDL_Event& e , Game* game);
		void update();
		void render(SDL_Renderer* renderer);
		SDL_Rect getRect() const;
    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		SDL_Rect rectPlayer;
		SDL_Texture* texture;
};

#endif
