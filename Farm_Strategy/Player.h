#pragma once
#include"Input.h"
#include"DxLib.h"
#include"MAPChangeData.h"

#define WIDTH 40
#define HEIGHT 40
#define MAP_SELL_LENGTH 10

class Player {
public:
	Player();
	~Player();
	void Update();
	void DrawPlayer();
	void Action();
public:
	int x; //プレイヤーのx座標
	int y; //プレイヤーのy座標
	int helf_w; //プレイヤーのx座標
	int helf_h; //プレイヤーのy座標

	Input input; //入力クラス
	RETURN_DATA data;
};