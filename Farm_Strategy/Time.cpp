#include"Time.h"

Time::Time() {
	this->time = 0;
	this->endTime = 5000;
	this->color_white = GetColor(255, 255, 255);
	this->color_black = GetColor(0, 0, 0);

}

Time::~Time() {}

void Time::Update() {
	time++;
}

void Time::DrawTime(int time) {
	DrawBox(0, 0, 80, 50, this->color_white, TRUE);
	DrawBox(5, 5, 75, 45, this->color_black, TRUE);
	DrawFormatString(20, 20, this->color_white,std::to_string(time/100).c_str());
}

void Time::InitTime() {
	this->time = 0;
}