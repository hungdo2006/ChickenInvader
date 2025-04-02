#ifndef CHICKEN_H
#define CHICKEN_H
#include <SDL.h>
#include <vector>
#include "Egg.h"
#include "Config.h"
using namespace std;
class Chicken
{
    public:
		Chicken(int x, int y, SDL_Texture* tex,  SDL_Texture* eggTexture,SDL_Texture* eggBrokenTex,SDL_Texture*boss);
		~Chicken();
        void takeDamage(int damage);
        bool getIsDead();
        void layEgg(SDL_Texture* eggTexture,SDL_Texture* eggBrokenTex);
		void update();
		void render(SDL_Renderer* renderer);
		void renderBoss(SDL_Renderer* renderer);
		SDL_Rect getRect() const;
        vector<Egg*>& getEggs();
        void removeEgg(int index);
        void setSize(int x , int y);
        void setHealth(int health);
        void setBoss();
        void setBossVel(int x , int y);
        int getHealth();
    private:
        bool isBoss = false;
        int health;
        int maxHealth = Chicken_MAX_HEALTH;
        bool isDead = false;
		int mPosX, mPosY;
		int mVelX, mVelY;
		SDL_Rect rectChicken;
		vector<Egg*> eggs;
		int eggTimer;
        SDL_Texture* chickenTexture;
        SDL_Texture* eggTexture;
        SDL_Texture* eggBrokenTexture;
        SDL_Texture* bossTexture;
};
#endif
