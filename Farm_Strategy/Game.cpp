#include"Game.h"

Game::Game() {
	this->fps= 144;
	this->mfps = 1000.f / fps;
	this->game_Mode = 0;
	this->end=0;
	this->now=0;
	this->looptime = 0;
	ChangeWindowMode(TRUE); //ウインドウモード(TRUE)・フルスクリーンモード(FALSE)の変更(DXライブラリ)
	SetGraphMode(600, 500, 32); //画面モードの変更(画面の解像度、カラービット数)
	DxLib_Init();   // DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先グラフィック領域の指定(DX_SCREEN_FRONT:表の画面　DX_SCREEN_BACK:裏の画面)

	SetTransColor(182, 185, 184); //グラフィックで透明色にする色をセット

	ClearDrawScreen(); //画面に描画されたものを消去する
}

Game::~Game() {}

void Game::Update() {
	this->player.Update();	
	this->time.Update();
	this->map.Update(this->player.data);
}

void Game::Draw() {
	this->time.DrawTime(this->time.time);
	this->map.DrawMAP();
	this->player.DrawPlayer();
}

void Game::Init() {
	this->map.LoadCropGraph();
	this->player.LoadToolGraph();
}