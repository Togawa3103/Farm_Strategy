#pragma once
#include"DxLib.h"
#include<vector>
typedef struct {
	int startFrame; //開始フレーム
	int endFrame; //終了フレーム
	int graphHandle; //画像ハンドル
}ANIMATION_DATA;

class Animation {
public:
	Animation();
	~Animation(); 
	void Update(); //フレームの更新
	void DrawAnima(int startX, int startY, int endX, int endY); //アニメの描写
public:
	int frame; //フレーム
	std::vector<ANIMATION_DATA> anima; //アニメーションデータ
};