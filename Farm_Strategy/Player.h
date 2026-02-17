#pragma once
#include"Input.h"
#include"DxLib.h"
#include"MAPChangeData.h"
#include"Tool.h"
#include"Animation.h"
#include"Sound.h"

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

#define MAP_MAX_LENGTHXY (WIDTH*MAP_SELL_LENGTH)/2

class Player {
public:
	Player();
	~Player();
	virtual void Update(int map[][HEIGHT]); //プレイヤーの更新
	void Update_StartMenu(int maxGameMode, int* selected_GameMode,int *gameMode); //スタートメニューのプレイヤーの更新
	void Update_ResultMenu(int maxGameMode, int* selected_GameMode, int* gameMode); //リザルトメニューのプレイヤーの更新

	virtual void DrawPlayer(); //プレイヤーの表示
	virtual void DrawScore(); //スコアの表示
	void DrawResult(); //スコアの表示

	virtual void DrawTools(); //ツールの表示
	virtual void Action(int map[][HEIGHT]); //入力による行動選択
	void Action_StartMenu(int maxGameMode, int * selected_GameMode, int* gameMode); //スタートメニューの入力による行動選択
	void Action_ResultMenu(int maxGameMode, int* selected_GameMode, int* gameMode); //リザルトメニューの入力による行動選択

	void InitData(); //Dataの初期化
	void LoadToolGraph(); //ツールの画像ロード
	//void SetScore(); //Actionの結果得られるスコアを設定
	//void GetCropNum(int cropNum); //作物番号の取得
	void SetMaxCropNum(int maxCropNum); //最大作物番号を設定
	//void PayCost(int cost); //コストの支払い
	int UpgradeTools(int toolNum); //ツールのアップグレード
	void SetNextCropNum(); //作物の変更
	void SetNextToolNum(); //ツールの変更

	virtual void InitPlayer(); //プレイヤー情報の初期化
public:
	int playerNum;
	int score;
	int toolNum; //ツール番号
	int x; //プレイヤーのx座標
	int y; //プレイヤーのy座標
	int helf_w; //プレイヤーのx座標
	int helf_h; //プレイヤーのy座標
	unsigned int color_red; //赤色
	unsigned int color_yellow; //黄色
	unsigned int color_black; //黒色
	unsigned int color_white; //白色
	int maxCropNum; //最大作物番号
	int cropNum; //今の作物番号
	Input input; //入力クラス
	Sound sound;
	SE* se;
	std::vector<RETURN_DATA> dataVec; //プレイヤーから渡すアクションの情報
	std::vector<Animation> animaVec;
};