#include "AudioManager.h"

Music AudioManager::bgMusic;
bool AudioManager::initialized = false;

void AudioManager::Init() {
    if (initialized) return;

    InitAudioDevice();

    // Load music
    bgMusic = LoadMusicStream("resources/Music/Ground Theme.mp3");
    PlayMusicStream(bgMusic);

    // Load SFX (add more as needed)
    //sfx["jump"] = LoadSound("resources/SFX/jump-small.wav");
    //sfx["coin"] = LoadSound("resources/SFX/coin.wav");

    initialized = true;
}

void AudioManager::PlayMusic() {
    PlayMusicStream(bgMusic);
}

void AudioManager::Update() {
    UpdateMusicStream(bgMusic);
}

void AudioManager::StopMusic() {
    StopMusicStream(bgMusic);
}

void AudioManager::SetBGMVolume(float vol) {
    SetMusicVolume(bgMusic, vol);
}