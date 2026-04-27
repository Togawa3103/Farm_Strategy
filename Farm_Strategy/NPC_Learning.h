#pragma once
#include"Player.h"
#include"Input_NPC_Learning.h"
#include"Crop.h"
#include"NPC.h"
class NPC_Learning : public Player {
public:
	NPC_Learning();
	~NPC_Learning();
	void Update(int time, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData); //プレイヤーの更新

	void DrawPlayer() override; //プレイヤーの表示
	//void DrawScore() override; //スコアの表示

	void DrawTools() override; //ツールの表示
	void Action(int map[][HEIGHT]) override; //入力による行動選択

	void InitPlayer() override; //NPC情報の初期化

public:
	InputNPC_Learning inputNPC;
	std::vector<CROP> myCropVec;
};