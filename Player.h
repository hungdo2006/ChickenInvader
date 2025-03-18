#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include "Config.h"
class Game;
class Player
{
    public:
		Player(Game* game,int x, int y);
		~Player();
		void reset();
        bool takeDamage(int damage);
        void heal(int healing);
		void handleInput( SDL_Event& e , Game* game);
		void update();
		void render(SDL_Renderer* renderer);
		SDL_Rect getRect() const;
    private:
        int health;
        const int maxHealth = Player_MAX_HEALTH;
		int mPosX, mPosY;
		int mVelX, mVelY;
		SDL_Rect rectPlayer;
		SDL_Texture* texture;
};

#endif
