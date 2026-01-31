#include "Player.h"
#include"Tool_picData.h"

Player::Player() {
	this->toolNum = 0;
	this->x = 0;
	this->y = 0;
	this->data.x = -1;
	this->data.y = -1;
	this->helf_w = (WIDTH * MAP_SELL_LENGTH) / 2;
	this->helf_h = (HEIGHT * MAP_SELL_LENGTH) / 2;
	this->color_red = GetColor(255, 0, 0);
	this->color_yellow = GetColor(255, 255, 0);
}

Player::~Player() {
}

void Player::Update() {
	this->InitData();
	this->input.Update();
	this->animaVec[this->toolNum].Update();
	this->Action();
}

void Player::DrawPlayer() {
	//DrawBox(285 + this->x, 230 + this->y, 295 + this->x, 240 + this->y, this->color_red,TRUE);	//	プレイヤー表示
	this->animaVec[this->toolNum].DrawAnima(265 + this->x, 210 + this->y, 295 + this->x, 240 + this->y);
	//カーソル表示
	DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
		MAPW_START_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH),
		MAPW_END_WIDTH + MAP_SELL_LENGTH * ((this->helf_w + this->x) / MAP_SELL_LENGTH),
		MAPW_END_HEIGHT + MAP_SELL_LENGTH * ((this->helf_h + this->y) / MAP_SELL_LENGTH), this->color_yellow, TRUE); 
}

void Player::Action() {
	if (this->input.keyState[KEY_INPUT_D]) { //キー「D」を押下しているとき
		if(x<200-1)this->x++;
	}
	if (this->input.keyState[KEY_INPUT_A]) { //キー「A」を押下しているとき
		if (x > -200)this->x--;
	}
	if (this->input.keyState[KEY_INPUT_S]) { //キー「S」を押下しているとき
		if (y < 200-1)this->y++;
	}
	if (this->input.keyState[KEY_INPUT_W]) { //キー「W」を押下しているとき
		if (y > -200)this->y--;
	}
	if (this->input.keyState[KEY_INPUT_SPACE]) { //キー「SPACE」を押下しているとき
		this->data = { (this->helf_w + this->x) / MAP_SELL_LENGTH ,(this->helf_h + this->y) / MAP_SELL_LENGTH, Action_SPACE};
	}
	if (this->input.keyState[KEY_INPUT_RETURN]) { //キー「RETURN」を押下しているとき
		this->data = { (this->helf_w + this->x) / MAP_SELL_LENGTH ,(this->helf_h + this->y) / MAP_SELL_LENGTH, Action_RETURN};
	}
}

void Player::InitData() {
	if (this->data.x!=-1&& this->data.y != -1) {
		this->data = { -1,-1 };
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