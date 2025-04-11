#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "raylib.h"
#include <string>

class AudioManager {
public:
    static void Init();
    static void PlayMusic();
    static void Update();
    static void StopMusic();
    void AudioManager::SetBGMVolume(float vol);

    static void PlaySFX(const std::string& name);

    static void Unload();

private:
    static Music bgMusic;
    static bool initialized;
};

#endif