#include"Time.h"

Time::Time() {
	this->time = 0;
	this->endTime = 10000;
	this->color_white = GetColor(255, 255, 255);
	this->color_black = GetColor(0, 0, 0);

}

Time::~Time() {}

void Time::Update() {
	time++;
}

void Time::DrawTime(int time) {
	DrawBox(0, 0, 50, 50, this->color_white, TRUE);
	DrawBox(5, 5, 45, 45, this->color_black, TRUE);
	DrawFormatString(20, 20, this->color_white,std::to_string(time/100).c_str());
}