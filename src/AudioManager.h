#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "raylib.h"
#include <string>

class AudioManager {
public:
    void Init();
    void PlayMusic();
    void Update();
    void StopMusic();
    void AudioManager::SetBGMVolume(float vol);

    void PlaySFX(const std::string& name);

    void Unload();

    Sound bgMusic;
    bool initialized;
};

#endif