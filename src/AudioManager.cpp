#include "AudioManager.h"

AudioManager::AudioManager()
{
    InitAudioDevice();
    musicLoaded = false;
}

AudioManager::~AudioManager()
{
    if (musicLoaded)
        UnloadMusicStream(music);
    CloseAudioDevice();
}

void AudioManager::LoadMusic(const std::string& filePath)
{
    music = LoadMusicStream(filePath.c_str());
    musicLoaded = true;
}

void AudioManager::PlayMusic()
{
    if (musicLoaded)
        PlayMusicStream(music);
}

void AudioManager::StopMusic()
{
    if (musicLoaded)
        StopMusicStream(music);
}

void AudioManager::SetVolume(float volume)
{
    if (musicLoaded)
        SetMusicVolume(music, volume);
}

void AudioManager::UpdateMusic()
{
    if (musicLoaded)
        UpdateMusicStream(music);
}
