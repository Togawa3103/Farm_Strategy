#pragma once
#include <time.h>
#include "DxLib.h"
#include"Input.h"
#include "Player.h"
#include "Time.h"
#include "MAP.h"
class Game {
public:
	Game();  //コンストラクタ 
	~Game(); //デストラクタ
	void Game_MainLoop(); //メインループ
	void Update();
	void Draw();
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
};