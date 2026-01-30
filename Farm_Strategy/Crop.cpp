#include"Crop.h"

CROP::CROP(int x,int y,int cropNum,int cropPicHandle) {
	this->color_green = GetColor(0, 255, 0);
	this->cropNum = cropNum;
	this->cropGrowth = 0;
	this->time = 0;
	this->x = x;
	this->y = y;
	this->cropPicHandle = cropPicHandle;
	this->deleteFlag = false;
}

CROP::~CROP(){
}

void CROP::Update() {
	this->time++;
	if (this->time==500) {
		this->cropGrowth++;
	}
}

void CROP::GrowUp(int cropPicHandle) {
	if (this->cropPicHandle!=cropPicHandle) {
		this->cropPicHandle = cropPicHandle;
	}
}