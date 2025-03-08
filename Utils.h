#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
int Random(int min, int max);
bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);

class LTexture{
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile(string path, SDL_Renderer* renderer);
        bool loadFromText(string text, SDL_Color textColor);
        void free();
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
        void renderT(int x, int y, SDL_Renderer * renderer);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;
        int width, height;
};

#endif
