#include "Player.h"

Player::Player() {
	this->x = 0;
	this->y = 0;
	this->data.x = -1;
	this->data.y = -1;
	this->helf_w = (WIDTH * MAP_SELL_LENGTH) / 2;
	this->helf_h = (HEIGHT * MAP_SELL_LENGTH) / 2;

}

Player::~Player() {
}

void Player::Update() {
	this->input.Update();
	this->Action();
}

void Player::DrawPlayer() {
	DrawBox(295 + this->x, 240 + this->y, 305 + this->x, 250 + this->y, GetColor(255, 0, 0),TRUE);	//	プレイヤー表示
}

void Player::Action() {
	if (this->input.keyState[KEY_INPUT_D]) { //キー「D」を押下しているとき
		this->x++;
	}
	if (this->input.keyState[KEY_INPUT_A]) { //キー「A」を押下しているとき
		this->x--;
	}
	if (this->input.keyState[KEY_INPUT_S]) { //キー「S」を押下しているとき
		this->y++;
	}
	if (this->input.keyState[KEY_INPUT_W]) { //キー「W」を押下しているとき
		this->y--;
	}
	if (this->input.keyState[KEY_INPUT_SPACE]) { //キー「SPACE」を押下しているとき
		this->data = { (this->helf_w + this->x) / MAP_SELL_LENGTH ,(this->helf_h + this->y) / MAP_SELL_LENGTH };
	}
}