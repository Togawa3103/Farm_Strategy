#pragma once
#include"DxLib.h"
#include"MAPChangeData.h"

#define WIDTH 40
#define HEIGHT 40
#define MAP_SELL_LENGTH 10
#define MAPW_START_WIDTH 100
#define MAPW_START_HEIGHT 45
#define MAPW_END_WIDTH MAPW_START_WIDTH+MAP_SELL_LENGTH
#define MAPW_END_HEIGHT MAPW_START_HEIGHT+MAP_SELL_LENGTH

#define MAPB_START_WIDTH 101
#define MAPB_START_HEIGHT 46
#define MAPB_END_WIDTH MAPB_START_WIDTH+MAP_SELL_LENGTH-2
#define MAPB_END_HEIGHT MAPB_START_HEIGHT+MAP_SELL_LENGTH-2

#define MAPBG_START_WIDTH 95
#define MAPBG_START_HEIGHT 40
#define MAPBG_END_WIDTH 505
#define MAPBG_END_HEIGHT 450


class MAP {
public:
	MAP();
	~MAP();
	void Update(RETURN_DATA data);
	void DrawMAP();
	void GetMAPChangeData(RETURN_DATA data); //Playerが行動を起こした座標の取得
public:
	int map[WIDTH][HEIGHT];
	unsigned int color_black; //黒色
	unsigned int color_white; //白色
	unsigned int color_red; //白色
};