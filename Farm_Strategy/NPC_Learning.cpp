#pragma once
#include "NPC_Learning.h"
#include"Tool_picDataNPC_Learning.h"
#include<string>

NPC_Learning::NPC_Learning() {
	this->playerNum = 2;
	this->score = 0;
	this->toolNum = 0;
	this->x = 0;
	this->y = 0;
	this->dataVec = { { this->playerNum ,-1,-1,-1,this->cropNum,-1, 0} };
	this->cropNum = 0;
	this->maxCropNum = maxCropNum;
	this->helf_w = (WIDTH * MAP_SELL_LENGTH) / 2;
	this->helf_h = (HEIGHT * MAP_SELL_LENGTH) / 2;
	this->color_red = GetColor(255, 0, 0);
	this->color_yellow = GetColor(255, 255, 0);
	this->color_white = GetColor(255, 255, 255);
	this->color_black = GetColor(0, 0, 0);
}

NPC_Learning::~NPC_Learning() {}

void NPC_Learning::Update(int time, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData) {
	this->InitData();
	this->inputNPC.InitInput();
	this->inputNPC.Update(time, this->toolNum, this->cropNum, this->score, (this->helf_w + this->x), (this->helf_h + this->y), map, cropVec, cropData, &tool_PicDataNPC_Learning);
	this->animaVec[this->toolNum].Update();
	this->Action(map);
}

void NPC_Learning::DrawPlayer() {
	this->DrawScore(700, 50);
	this->DrawTools();
	//DrawBox(285 + this->x, 230 + this->y, 295 + this->x, 240 + this->y, this->color_red,TRUE);	//	プレイヤー表示
	this->animaVec[this->toolNum].DrawAnima(this->helf_w + this->x + 50, this->helf_h + this->y - 10,
		this->helf_w + this->x + 95, this->helf_h + this->y + 35);
	//カーソル表示
	DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
		MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH),
		MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
		MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH), this->color_red, TRUE);

	//ツールがアップグレードされているとき
	if (tool_PicDataNPC_Learning[this->toolNum].toolLevel > 0) {
		for (int i = 1; i < 5; i++) {
			if ((this->helf_w + this->x) / MAP_SELL_LENGTH > 0) {
				if (tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].leftX != 0) {
					DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].leftX),
						MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH),
						MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].leftX),
						MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH), this->color_red, TRUE);
				}
			}
			if ((this->helf_w + this->x) / MAP_SELL_LENGTH < WIDTH - 1) {
				if (tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].rightX != 0) {
					DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].rightX),
						MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH),
						MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].rightX),
						MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH), this->color_red, TRUE);
				}
			}
			if ((this->helf_h + this->y) / MAP_SELL_LENGTH > 0) {
				if (tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].upY != 0) {
					DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
						MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH + tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].upY),
						MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
						MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH + tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].upY),
						this->color_red, TRUE);
				}
			}
			if ((this->helf_h + this->y) / MAP_SELL_LENGTH < HEIGHT - 1) {
				if (tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].downY != 0) {
					DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
						MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH + tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].downY),
						MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
						MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH + tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].downY),
						this->color_red, TRUE);
				}
			}
		}
	}
}

void NPC_Learning::Action(int map[][HEIGHT]) {
	if (this->inputNPC.keyState[KEY_INPUT_D]) { //キー「D」を押下しているとき
		if (x < MAP_MAX_LENGTHXY - 1)this->x++;
	}
	if (this->inputNPC.keyState[KEY_INPUT_A]) { //キー「A」を押下しているとき
		if (x > -MAP_MAX_LENGTHXY)this->x--;
	}
	if (this->inputNPC.keyState[KEY_INPUT_S]) { //キー「S」を押下しているとき
		if (y < MAP_MAX_LENGTHXY - 1)this->y++;
	}
	if (this->inputNPC.keyState[KEY_INPUT_W]) { //キー「W」を押下しているとき
		if (y > -MAP_MAX_LENGTHXY)this->y--;
	}
	if (this->inputNPC.keyState[KEY_INPUT_SPACE]) { //キー「SPACE」を押下しているとき
		int playerX = (this->helf_w + this->x) / MAP_SELL_LENGTH;
		int playerY = (this->helf_h + this->y) / MAP_SELL_LENGTH;
		if (map[playerX][playerY] == (this->toolNum + 1) / 2*2) {
			//アクションデータの追加
			this->dataVec.push_back({ this->playerNum ,playerX ,playerY, Action_SPACE, this->cropNum, this->toolNum, this->score });
		}
		if (playerX > 0) {
			int toolPower = tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].leftX;//強化したツールで範囲が拡張されているか
			if (toolPower != 0) {
				if (map[playerX + toolPower][playerY] == (this->toolNum + 1) / 2 * 2) {
					//アクションデータの追加
					this->dataVec.push_back({ this->playerNum ,playerX + toolPower,
							playerY,
							Action_SPACE,
							this->cropNum,
							this->toolNum,
							0 });
				}
			}
		}
		if (playerX < WIDTH - 1) {
			int toolPower = tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].rightX;//強化したツールで範囲が拡張されているか
			if (toolPower != 0) {
				if (map[playerX + toolPower][playerY] == (this->toolNum + 1) / 2 * 2) {
					//アクションデータの追加
					this->dataVec.push_back({ this->playerNum ,playerX + toolPower
						,playerY,
						Action_SPACE,
						this->cropNum,
						this->toolNum,
						0 });
				}
			}
		}
		if (playerY > 0) {
			int toolPower = tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].upY;//強化したツールで範囲が拡張されているか
			if (toolPower != 0) {
				if (map[playerX][playerY + toolPower] == (this->toolNum + 1) / 2 * 2) {
					//アクションデータの追加
					this->dataVec.push_back({ this->playerNum ,playerX,
						playerY + toolPower,
						Action_SPACE,
						this->cropNum,
						this->toolNum,
						0 });
				}
			}
		}
		if (playerY < HEIGHT - 1) {
			int toolPower = tool_PicDataNPC_Learning[this->toolNum].toolUpgradeData[tool_PicDataNPC_Learning[this->toolNum].toolLevel].downY;//強化したツールで範囲が拡張されているか
			if (toolPower != 0) {
				if (map[playerX][playerY + toolPower] == (this->toolNum + 1) / 2 * 2) {
					//アクションデータの追加
					this->dataVec.push_back({ this->playerNum ,playerX,
						playerY + toolPower,
						Action_SPACE,
						this->cropNum,
						this->toolNum,
						0 });
				}
			}
		}
	}
	if (this->inputNPC.keyState[KEY_INPUT_RETURN]) { //キー「RETURN」を押下しているとき
		int playerX = (this->helf_w + this->x) / MAP_SELL_LENGTH;
		int playerY = (this->helf_h + this->y) / MAP_SELL_LENGTH;
		this->dataVec.push_back({ this->playerNum , playerX ,playerY, Action_RETURN, this->cropNum, this->toolNum, 0 });
	}
	if (this->inputNPC.keyState[KEY_INPUT_E]) {//キー「E」を押下しているとき
		this->SetNextToolNum();
	}
	if (this->inputNPC.keyState[KEY_INPUT_Q]) {//キー「Q」を押下しているとき
		this->SetNextCropNum();
	}
	if (this->inputNPC.keyState[KEY_INPUT_Z]) {//キー「Z」を押下しているとき
		this->UpgradeTools(&tool_PicDataNPC_Learning, this->toolNum);
	}

}

/*
void NPC::DrawScore(int x, int y) {
	DrawBox(x, y, x+8, 100, this->color_white, TRUE);
	DrawBox(x+5, y+5, 775, 95, this->color_black, TRUE);
	DrawFormatString(720, 70, this->color_white, std::to_string(score).c_str());
}
*/

void NPC_Learning::DrawTools() {
	for (int i = 0; i < Tool_MAX; i++) {
		if (tool_PicDataNPC_Learning[i].toolLevel < tool_PicDataNPC_Learning[i].maxLevel && tool_PicDataNPC_Learning[i].toolUpgradeData[tool_PicDataNPC_Learning[i].toolLevel].upgrade_cost < this->score) {
			DrawBox(700, 150 + (i * 50), 800, 200 + (i * 50), this->color_yellow, TRUE);
		}
		else {
			DrawBox(700, 150 + (i * 50), 800, 200 + (i * 50), this->color_white, TRUE);
		}
		DrawBox(705, 155 + (i * 50), 795, 195 + (i * 50), this->color_black, TRUE);
		this->animaVec[i].DrawAnima(705, 155 + (i * 50), 745, 195 + (i * 50));
		DrawFormatString(750, 155 + (i * 50), this->color_white, ("LV:" + std::to_string(tool_PicDataNPC_Learning[i].toolLevel + 1)).c_str());
		DrawFormatString(750, 175 + (i * 50), this->color_white, std::to_string(tool_PicDataNPC_Learning[i].toolUpgradeData[tool_PicDataNPC_Learning[i].toolLevel].upgrade_cost).c_str());
	}
}

void NPC_Learning::InitPlayer() {
	this->score = 0;
	this->toolNum = 0;
	this->x = 0;
	this->y = 0;
	this->dataVec = { {this->playerNum, -1,-1,-1,this->cropNum,-1, 0} };
	this->cropNum = 0;
	this->maxCropNum = maxCropNum;
	this->input.frame = 0;
	for (int i = 0; i < Tool_MAX; i++) {
		tool_PicDataNPC_Learning[i].toolLevel = 0;
	}
	this->inputNPC.InitCropGrownVec();
}