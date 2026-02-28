#pragma once
#include"Player.h"
#include"Input_NPC.h"
#include"Crop.h"
class NPC : public Player {
public:
	NPC();
	~NPC();
	void Update(int map[][HEIGHT],std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData); //プレイヤーの更新
	
	void DrawPlayer() override; //プレイヤーの表示
	void DrawScore() override; //スコアの表示
	
	void DrawTools() override; //ツールの表示
	void Action(int map[][HEIGHT]) override; //入力による行動選択
	
	void InitPlayer() override; //NPC情報の初期化

public:
	InputNPC inputNPC;
	std::vector<CROP> myCropVec;
};