#include "SoundManager.h"
using namespace std;

Mix_Chunk* SoundManager::shootSound = nullptr;
Mix_Chunk* SoundManager::explosionSound = nullptr;
Mix_Music* SoundManager::backgroundMusic = nullptr;
Mix_Chunk* SoundManager::eggSound = nullptr;
Mix_Chunk* SoundManager::buttonClickSound = nullptr;

bool SoundManager::loadSounds() {
    shootSound = Mix_LoadWAV("assets/sounds/shoot1.wav");
    explosionSound = Mix_LoadWAV("assets/sounds/quack.wav");
    backgroundMusic = Mix_LoadMUS("assets/sounds/music.mp3");
    eggSound = Mix_LoadWAV("assets/sounds/egg.wav");
    buttonClickSound = Mix_LoadWAV("assets/sounds/button.wav");

    if (!shootSound || !explosionSound || !backgroundMusic|| !eggSound|| !buttonClickSound) {
        cout << "Failed to load audio: " << Mix_GetError() << endl;
        return false;
    }

    return true;
}

void SoundManager::playShootSound() {
    Mix_PlayChannel(-1, shootSound, 0);
}

void SoundManager::playExplosionSound() {
    Mix_PlayChannel(-1, explosionSound, 0);
}

void SoundManager::playBackgroundMusic() {
    Mix_PlayMusic(backgroundMusic, -1);
}

void SoundManager::playEggSound(){
    Mix_PlayChannel(-1,eggSound,0);
}

void SoundManager::playClickSound(){
    Mix_PlayChannel(-1,buttonClickSound,0);
}
void SoundManager::clean() {
    Mix_FreeChunk(shootSound);
    Mix_FreeChunk(explosionSound);
    Mix_FreeChunk(eggSound);
    Mix_FreeChunk(buttonClickSound);
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
}
