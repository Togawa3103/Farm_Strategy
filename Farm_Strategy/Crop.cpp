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
	//this->anima=anima;
}

CROP::~CROP(){
}

void CROP::Update() {
	this->time++;
	this->anima[this->cropGrowth].Update();
	if (this->time==500) {
		this->cropGrowth++;
	}
}

void CROP::GrowUp(int cropPicHandle) {
	if (this->cropPicHandle!=cropPicHandle) {
		this->cropPicHandle = cropPicHandle;
	}
}

void CROP::DrawCrop(int startX, int startY, int endX, int endY) {
	this->anima[this->cropGrowth].DrawAnima(startX,startY,endX,endY);
}