#pragma once
#include"DxLib.h"
class Sound {
public:
	Sound();
	~Sound();
	void PlayBGMSound();
	void LoadSound(const char* SoundName);
	void StopSound();
public:
	int soundHandle;
};