#pragma once
#include <time.h>
#include "DxLib.h"
#include"Input.h"
#include "Player.h"
#include "Time.h"
#include "MAP.h"

enum {
	StartMenu_Start,
	StartMenu_Continue,
	StartMenu_Max,
};

//スタート画面の選択肢の文字列
typedef struct {
	const char* startmenu_name;
}StartMenu;

//スタート画面の選択肢の文字列
static StartMenu start[] = {
	{"はじめから"},
	{"つづきから"},
};

class Game {
public:
	Game();  //コンストラクタ 
	~Game(); //デストラクタ
	void Game_MainLoop(); //メインループ
	void Game_StartLoop(); //メインループ
	void Update(); //ゲームの行進
	void Update_StartMenu(int* selected_GameMode, int *gameMode); //ゲームの行進
	void Draw(); //ゲームの描写
	void DrawStartMenu(unsigned int Color1, unsigned int Color2, int selectedMenu);
	void Init(); //ゲームの初期化
	void LoadSE();
public:
	int game_Mode; //ゲームの状態
	int fps; //FPS
	float mfps; //1フレームの時間
	clock_t end; //前フレームの終了時間
	clock_t now; //現在の時間
	double looptime; //1フレームにかかった時間
	
	Player player; //プレイヤークラス
	Time time; //Timeクラス
	MAP map; //MAPクラス

	int gameMode;
	
};