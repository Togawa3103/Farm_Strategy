#pragma once
#include<vector>

typedef struct {
	const char* toolPicName; //作物の画像名
	int toolPicHandle; //作物画像ハンドル
	int startFrame; //スタートフレーム
	int endFrame; //エンドフレーム
}TOOL_DATA;

typedef struct {
	int upgrade_cost;
	int leftX;
	int upY;
	int rightX;
	int downY;
}UPGRADE_DATA;

typedef struct {
	int toolNum; //ツール番号
	int toolLevel; //レベル
	int maxLevel; //最大レベル
	std::vector<TOOL_DATA> toolPicDataVec; //作物データリスト
	std::vector<UPGRADE_DATA> toolUpgradeData; //レベルによる強化度
}TOOL_PIC;

