#pragma once
#include"DxLib.h"

class Input {
public:
	char keyState[256]; //キー入力配列
	int frame; //フレーム数
public:
	Input();
	~Input();
	void Update(int toolNum); //キー入力更新
	void InitInput(); //入力初期化
};