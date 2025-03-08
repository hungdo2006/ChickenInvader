#include <bits/stdc++.h>
#include "Game.h"

using namespace std;

int main()
{
    Game game;
    if (!game.init()) {
        cout  << "Game initialization failed!" << endl;
        return 1;
    }else if(!game.loadMedia()){
        cout  << "Game media loading failed!" << endl;
        return 1;
    }else{
            while(game.running){
                game.handleEvents();
                game.update();
                game.render();
        }
    }
    game.close();
    return 0;
}
