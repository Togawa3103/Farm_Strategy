#pragma once
#include"DxLib.h"
enum {
	Tool_InputNPC_Hoe,
	Tool_InputNPC_WateringCan,
	Tool_InputNPC_Scissors,
	Tool_InputNPC_MAX,
};
typedef struct {
	int x;
	int y;
}GROWNCROP;

typedef struct {
	int x;
	int y;
}COORDINATE;

class Input {
public:
	char keyState[256]; //キー入力配列
	int frame; //フレーム数
public:
	Input();
	~Input();
	virtual void Update(int toolNum); //キー入力更新
	void InitInput(); //入力初期化
	void Update_StartMenu(); //スタート画面のキー入力更新
	void Update_ResultMenu(); //リザルト画面のキー入力更新
};