#include <bits/stdc++.h>
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

int main(int argc, char* argv[])
{
    Game game;
    if (!game.init()) {
        cout  << "Game initialization failed!" << endl;
        return 1;
    }
    game.run();

    return 0;
}
