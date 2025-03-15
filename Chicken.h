#ifndef CHICKEN_H
#define CHICKEN_H
#include <SDL.h>
#include <vector>
#include "Egg.h"
using namespace std;
class Game;
class Chicken
{
    public:
		Chicken(Game* game, int x, int y, SDL_Texture* tex,  SDL_Texture* eggTexture,SDL_Texture* eggBrokenTex);
		~Chicken();
        void takeDamage(int damage);
        bool getIsDead();
        void layEgg(SDL_Texture* eggTexture,SDL_Texture* eggBrokenTex);
		void update();
		void render(SDL_Renderer* renderer);
		SDL_Rect getRect() const;
        vector<Egg*>& getEggs();
        void removeEgg(int index);
    private:
        int health;
        const int maxHealth = 100;
        bool isDead = false;
		int mPosX, mPosY;
		int mVelX, mVelY;
		SDL_Rect rectChicken;
		vector<Egg*> eggs;
		int eggTimer;
        SDL_Texture* chickenTexture;
        SDL_Texture* eggTexture;
        SDL_Texture* eggBrokenTexture;
};
#endif
