#pragma once
#include "raylib.h"
#include <string>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void LoadMusic(const std::string& filePath);
	void PlayMusic();
	void StopMusic();
	void SetVolume(float volume);
	void UpdateMusic();

private:
	Music music;
	bool musicLoaded;
};