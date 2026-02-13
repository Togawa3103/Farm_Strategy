#include"Sound.h"

Sound::Sound() {}
Sound::~Sound() {}
void Sound::LoadSound(const char* SoundName) {
	this->soundHandle = LoadSoundMem(SoundName);
	ChangeVolumeSoundMem(100, this->soundHandle);
}

void Sound::PlayBGMSound(int seHandel) {
	PlaySoundMem(seHandel, DX_PLAYTYPE_BACK);
}

void Sound::StopSound() {
	StopSoundMem(this->soundHandle);
}