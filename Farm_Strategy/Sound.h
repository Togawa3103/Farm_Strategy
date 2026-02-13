#pragma once
#include"DxLib.h"
typedef struct {
	const char* seName;
	int seSoundHandle;
}SE;

enum {
	SE_HOE,
	SE_WATERCAN,
	SE_SCISSORS,
	SE_UPGRADE,
	SE_UPGRADEMISS,
	SE_SELECTCROP,
	SE_SELECTTOOL,
	SE_MAX
};

class Sound {
public:
	Sound();
	~Sound();
	void PlayBGMSound(int seHandle);
	void LoadSound(const char* SoundName);
	void StopSound();
public:
	int soundHandle;
};