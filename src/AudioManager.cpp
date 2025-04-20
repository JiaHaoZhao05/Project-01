#include "AudioManager.h"

void AudioManager::Init() {
    if (initialized) return;

    // Load music
    bgMusic = LoadSound("resources/Music/Ground Theme.mp3");

    // Load SFX (add more as needed)
    //sfx["jump"] = LoadSound("resources/SFX/jump-small.wav");
    //sfx["coin"] = LoadSound("resources/SFX/coin.wav");

    initialized = true;
}

void AudioManager::PlayMusic() {
    PlaySound(bgMusic);
}

void AudioManager::Update() {
    //UpdateMusicStream(bgMusic);
}

void AudioManager::StopMusic() {
    //StopMusicStream(bgMusic);
}

void AudioManager::SetBGMVolume(float vol) {
    //SetMusicVolume(bgMusic, vol);
}