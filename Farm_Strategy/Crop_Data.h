#pragma once
#include<vector>

typedef struct {
	int cropGrow; //作物成長度
	const char* cropPicName; //作物の画像名
	int cropPicHandle; //作物画像ハンドル
	int startFrame; //スタートフレーム
	int endFrame; //エンドフレーム
}CROP_DATA;

typedef struct {
	int cropNum; //作物番号
	int maxGrowth; //作物最大成長度
	int score;
	std::vector<CROP_DATA> cropPicDataVec; //作物データリスト
}CROP_PIC;
