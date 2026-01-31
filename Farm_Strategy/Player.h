#pragma once
#include"Input.h"
#include"DxLib.h"
#include"MAPChangeData.h"
#include"Tool.h"
#include"Animation.h"

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


class Player {
public:
	Player();
	~Player();
	void Update(); //プレイヤーの更新
	void DrawPlayer(); //プレイヤーの表示
	void Action(); //入力による行動選択
	void InitData(); //Dataの初期化
	void LoadToolGraph(); //ツールの画像ロード
public:
	int toolNum;
	int x; //プレイヤーのx座標
	int y; //プレイヤーのy座標
	int helf_w; //プレイヤーのx座標
	int helf_h; //プレイヤーのy座標
	unsigned int color_red; //赤色
	unsigned int color_yellow; //黄色

	Input input; //入力クラス
	RETURN_DATA data; //プレイヤーから渡すアクションの情報
	std::vector<Animation> animaVec;
};