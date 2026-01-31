#pragma once
#include<vector>

typedef struct {
	const char* toolPicName; //作物の画像名
	int toolPicHandle; //作物画像ハンドル
	int startFrame; //スタートフレーム
	int endFrame; //エンドフレーム
}TOOL_DATA;

typedef struct {
	int toolNum; //ツール番号
	std::vector<TOOL_DATA> toolPicDataVec; //作物データリスト
}TOOL_PIC;

