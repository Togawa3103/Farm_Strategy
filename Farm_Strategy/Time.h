#pragma once
#include"DxLib.h"
#include<string>
class Time {
public:
	Time();
	~Time();
	void Update(); //時間更新
	void DrawTime(int time); //時間表示

public:
	int time; //時間カウント
	int endTime; //終了時間
	unsigned int color_black; //黒色
	unsigned int color_white; //白色

};