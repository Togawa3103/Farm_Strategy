#include "Player.h"
#include"Tool_picData.h"
#include<string>

Player::Player() {
	this->score = 0;
	this->toolNum = 0;
	this->x = 0;
	this->y = 0;
	this->dataVec = { { -1,-1,-1,this->cropNum,-1, 0} };
	this->cropNum=0;
	this->maxCropNum = maxCropNum;
	this->helf_w = (WIDTH * MAP_SELL_LENGTH) / 2;
	this->helf_h = (HEIGHT * MAP_SELL_LENGTH) / 2;
	this->color_red = GetColor(255, 0, 0);
	this->color_yellow = GetColor(255, 255, 0);
	this->color_white = GetColor(255, 255, 255);
	this->color_black = GetColor(0, 0, 0);
}

Player::~Player() {
}

void Player::Update() {
	this->InitData();
	this->input.InitInput();
	this->input.Update(this->toolNum);
	this->animaVec[this->toolNum].Update();
	this->Action();
}

void Player::DrawPlayer() {
	this->DrawScore();
	this->DrawTools();
	//DrawBox(285 + this->x, 230 + this->y, 295 + this->x, 240 + this->y, this->color_red,TRUE);	//	プレイヤー表示
	this->animaVec[this->toolNum].DrawAnima(this->helf_w + this->x +50, this->helf_h + this->y -10,
		this->helf_w + this->x + 95, this->helf_h + this->y + 35);
	//カーソル表示
	DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
		MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH),
		MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
		MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH), this->color_yellow, TRUE); 
	for (int i = 1; i < 5; i++) {
		if (tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].leftX != 0) {
			DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].leftX),
				MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH),
				MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].leftX),
				MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH), this->color_yellow, TRUE);
		}
		if (tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].rightX != 0) {
			DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].rightX),
				MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH),
				MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].rightX),
				MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH), this->color_yellow, TRUE);
		}
		if (tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].upY != 0) {
			DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
				MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].upY),
				MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
				MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].upY),
				this->color_yellow, TRUE);
		}
		if (tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].downY != 0) {
			DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
				MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH+tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].downY),
				MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
				MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH+ tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].downY),
				this->color_yellow, TRUE);
		}
	}
}

void Player::Action() {
	if (this->input.keyState[KEY_INPUT_D]) { //キー「D」を押下しているとき
		if(x< MAP_MAX_LENGTHXY -1)this->x++;
	}
	if (this->input.keyState[KEY_INPUT_A]) { //キー「A」を押下しているとき
		if (x > -MAP_MAX_LENGTHXY)this->x--;
	}
	if (this->input.keyState[KEY_INPUT_S]) { //キー「S」を押下しているとき
		if (y < MAP_MAX_LENGTHXY -1)this->y++;
	}
	if (this->input.keyState[KEY_INPUT_W]) { //キー「W」を押下しているとき
		if (y > -MAP_MAX_LENGTHXY)this->y--;
	}
	if (this->input.keyState[KEY_INPUT_SPACE]) { //キー「SPACE」を押下しているとき
		this->dataVec.push_back({ (this->helf_w + this->x) / MAP_SELL_LENGTH ,(this->helf_h + this->y) / MAP_SELL_LENGTH, Action_SPACE, this->cropNum, this->toolNum, this->score });
		if (tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].leftX != 0) {
			this->dataVec.push_back({ (this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].leftX 
				,(this->helf_h + this->y) / MAP_SELL_LENGTH,
				Action_SPACE,
				this->cropNum,
				this->toolNum,
				0 });
		}
		if (tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].rightX != 0) {
			this->dataVec.push_back({ (this->helf_w + this->x) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].rightX
				,(this->helf_h + this->y) / MAP_SELL_LENGTH,
				Action_SPACE,
				this->cropNum,
				this->toolNum,
				0 });
		}
		if (tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].upY != 0) {
			this->dataVec.push_back({ (this->helf_w + this->x) / MAP_SELL_LENGTH,
				(this->helf_h + this->y) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].upY,
				Action_SPACE,
				this->cropNum,
				this->toolNum,
				0 });
		}
		if (tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].downY != 0) {
			this->dataVec.push_back({ (this->helf_w + this->x) / MAP_SELL_LENGTH,
				(this->helf_h + this->y) / MAP_SELL_LENGTH + tool_PicData[this->toolNum].toolUpgradeData[tool_PicData[this->toolNum].toolLevel].downY,
				Action_SPACE,
				this->cropNum,
				this->toolNum,
				0 });
		}
	}
	if (this->input.keyState[KEY_INPUT_RETURN]) { //キー「RETURN」を押下しているとき
		this->dataVec.push_back({ (this->helf_w + this->x) / MAP_SELL_LENGTH ,(this->helf_h + this->y) / MAP_SELL_LENGTH, Action_RETURN, this->cropNum, this->toolNum, 0});
	}
	if (this->input.keyState[KEY_INPUT_E]) {//キー「E」を押下しているとき
		this->SetNextToolNum();
	}
	if (this->input.keyState[KEY_INPUT_Q]) {//キー「Q」を押下しているとき
		this->SetNextCropNum();
	}
	if (this->input.keyState[KEY_INPUT_Z]) {//キー「Z」を押下しているとき
		this->UpgradeTools(this->toolNum);
	}
}

void Player::InitData() {
	if (this->dataVec.size()>0||(this->dataVec[0].x != -1 && this->dataVec[0].y != -1)) {
		this->dataVec = { { -1,-1,-1,this->cropNum,-1, 0} };
	}
}

void Player::LoadToolGraph() {
	for (int i = 0; i < tool_PicData.size(); i++) {
		Animation anima;
		this->animaVec.push_back(anima);
		for (int j = 0; j < tool_PicData[i].toolPicDataVec.size();j++) {
			tool_PicData[i].toolPicDataVec[j].toolPicHandle = LoadGraph(tool_PicData[i].toolPicDataVec[j].toolPicName);
			ANIMATION_DATA animaData = { tool_PicData[i].toolPicDataVec[j].startFrame, tool_PicData[i].toolPicDataVec[j].endFrame,
				tool_PicData[i].toolPicDataVec[j].toolPicHandle };
			this->animaVec[tool_PicData[i].toolNum].anima.push_back(animaData);
		}
	}
}

void Player::DrawScore() {
	DrawBox(0, 50, 50, 100, this->color_white, TRUE);
	DrawBox(5, 55, 45, 95, this->color_black, TRUE);
	DrawFormatString(20, 70, this->color_white, std::to_string(score).c_str());
}

void Player::DrawTools() {
	for (int i = 0; i < Tool_MAX; i++) {
		if (tool_PicData[i].toolLevel < tool_PicData[i].maxLevel && tool_PicData[i].toolUpgradeData[tool_PicData[i].toolLevel].upgrade_cost < this->score) {
			DrawBox(0, 150 + (i * 50), 100, 200 + (i * 50), this->color_yellow, TRUE);
		}
		else {
			DrawBox(0, 150 + (i * 50), 100, 200 + (i * 50), this->color_white, TRUE);
		}
		DrawBox(5, 155 + (i * 50), 95, 195 + (i * 50), this->color_black, TRUE);
		this->animaVec[i].DrawAnima(5, 155 + (i * 50), 45, 195 + (i * 50));
		DrawFormatString(50, 155 + (i * 50), this->color_white, ("LV:"+std::to_string(tool_PicData[i].toolLevel + 1)).c_str());
		DrawFormatString(50, 175 + (i * 50), this->color_white, std::to_string(tool_PicData[i].toolUpgradeData[tool_PicData[i].toolLevel].upgrade_cost).c_str());
	}
}

/*
void Player::SetScore() {
	for (int i = 0; i < this->dataVec.size(); i++) {
		this->score = this->score + this->dataVec[i].score;
	}
}
*/
void Player::SetMaxCropNum(int maxCropNum) {
	this->maxCropNum = maxCropNum;
}
/*
void Player::PayCost(int cost) {
	this->score = this->score - cost;
}
*/

int Player::UpgradeTools(int toolNum) {
	if (tool_PicData[toolNum].toolLevel<tool_PicData[toolNum].maxLevel) {
		if (tool_PicData[toolNum].toolUpgradeData[tool_PicData[toolNum].toolLevel].upgrade_cost < this->score) {
			this->score = this->score - tool_PicData[toolNum].toolUpgradeData[tool_PicData[toolNum].toolLevel].upgrade_cost;
			tool_PicData[toolNum].toolLevel++;
			this->sound.LoadSound("Sound/決定ボタンを押す40.mp3");
			this->sound.PlayBGMSound();
			return 0;
		}
	}
	this->sound.LoadSound("Sound/ビープ音4.mp3");
	this->sound.PlayBGMSound();
	return -1;
}

void Player::SetNextCropNum() {
	this->cropNum = (this->cropNum + 1) % this->maxCropNum;
	this->sound.LoadSound("Sound/カーソル移動2.mp3");
	this->sound.PlayBGMSound();
}

void Player::SetNextToolNum() {
	this->toolNum = (this->toolNum + 1) % Tool_MAX; 
	this->sound.LoadSound("Sound/カーソル移動1.mp3");
	this->sound.PlayBGMSound();
}