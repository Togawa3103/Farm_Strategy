#pragma once
#include"DxLib.h"
#include<vector>
#include"Crop_Data.h"
#include "Animation.h"

class CROP {
public:
	CROP(int x, int y, int cropNum, int cropMaxGrowth, int score, int cropPicHandle);
	~CROP();
	void Update(); // CROPの更新
	void GrowUp(int cropPicHandle); //成長後の表示する画像の更新
	void DrawCrop(int startX, int startY, int endX, int endY); //作物の表示
public:
	int cropNum; //作物番号
	int cropMaxGrowth; //作物成長限界
	int cropGrowth; //作物成長段階
	int score; //作物スコア
	int time; //育成時間
	int x; //x座標
	int y; //y座標
	unsigned int color_green; //色
	int cropPicHandle; //表示する画像のハンドル
	bool deleteFlag;
	std::vector<Animation> anima;
};