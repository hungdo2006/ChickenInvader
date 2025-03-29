#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <iostream>

class SoundManager {
public:
    static bool loadSounds();
    static void playShootSound();
    static void playExplosionSound();
    static void playBackgroundMusic();
    static void playEggSound();
    static void playClickSound();
    static void clean();

private:
    static Mix_Chunk* shootSound;
    static Mix_Chunk* explosionSound;
    static Mix_Music* backgroundMusic;
    static Mix_Chunk* eggSound;
    static Mix_Chunk* buttonClickSound;

};

#endif
