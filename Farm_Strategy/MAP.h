#pragma once
#include"DxLib.h"
#include"MAPChangeData.h"
#include"Crop.h"
#include"Sound.h"
#include<vector>

#define WIDTH 40
#define HEIGHT 40
#define MAP_SELL_LENGTH 15
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
#define MAPBG_END_WIDTH 705
#define MAPBG_END_HEIGHT 650


class MAP {
public:
	MAP();
	~MAP();
	void Update(int *playerScore, std::vector<RETURN_DATA>& dataVec); //マップの更新
	void DrawMAP(); //マップの表示
	void DrawNumCrop(int cropNum); //今の作物の表示
	void DrawNPCNumCrop(int cropNum); //今の作物の表示
	void GetMAPChangeData(int *playerScore,RETURN_DATA *data); //Playerが行動を起こした座標の取得
	void UpdateCROP(); //すべての作物の更新
	void DeleteCROP(int x,int y); //作物の削除
	void LoadCropGraph(); //画像をロード
	int ReturnScore(int x, int y); //画像をロード
	void InitMAP(); //マップ情報の初期化
public:
	std::vector<CROP> cropVec; //すべての作物
	std::vector<Animation> animaVec; //すべての作物のアニメーション
	Sound sound;
	SE* se;
	int map[WIDTH][HEIGHT]; //マップの情報
	int maxCropNum;
	unsigned int color_black; //黒色
	unsigned int color_white; //白色
	unsigned int color_red; //赤色
};