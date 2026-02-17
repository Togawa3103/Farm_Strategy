#pragma once
#include <time.h>
#include "DxLib.h"
#include "Input.h"
#include "Player.h"
#include "Time.h"
#include "MAP.h"
#include "NPC.h"

enum {
	StartMenu_Solo,
	StartMenu_VS,
	StartMenu_End,
	StartMenu_Max,
};

enum {
	ResultMenu_Again,
	ResultMenu_End,
	ResultMenu_Max,
};

//スタート画面の選択肢の文字列
typedef struct {
	const char* menu_name;
}MenuString;

//スタート画面の選択肢の文字列
static MenuString start[] = {
	{"ひとりで"},
	{"たいせん"},
	{"やめる"}
};

static MenuString result[] = {
	{"もういちど"},
	{"やめる"},
};

class Game {
public:
	Game();  //コンストラクタ 
	~Game(); //デストラクタ
	void Game_MainLoop(); //メインループ
	void Game_MainVSLoop(); //メインループ
	void Game_StartLoop(); //スタート画面ループ
	void Game_ResultLoop(); //リザルト画面ループ
	void Update(); //ゲームの更新(一人用)
	void Update_VS(); //ゲームの更新(対戦用)

	void Update_StartMenu(int* selected_GameMode, int *gameMode); //スタート画面でのゲームの更新
	void Update_ResultMenu(int* selected_GameMode, int* gameMode); //リザルト画面でのゲームの更新

	void Draw(); //ゲームの描写(一人用)
	void Draw_VS(); //ゲームの描写(対戦用)

	void DrawResult(unsigned int Color1, unsigned int Color2, int selectedMenu); //結果の描写
	void DrawStartMenu(unsigned int Color1, unsigned int Color2, int selectedMenu);//スタートメニューの描写
	void DrawResultMenu(unsigned int Color1, unsigned int Color2, int selectedMenu);//リザルトメニューの描写

	void Init(); //ゲームの初期化
	void LoadSE(); //SEのロード
public:
	//int game_Mode; //ゲームの状態
	int fps; //FPS
	float mfps; //1フレームの時間
	clock_t end; //前フレームの終了時間
	clock_t now; //現在の時間
	double looptime; //1フレームにかかった時間
	
	Player player; //プレイヤークラス
	NPC npc; //NPCクラス
	Time time; //Timeクラス
	MAP map; //MAPクラス

	int gameMode; //ゲームモード
	
};