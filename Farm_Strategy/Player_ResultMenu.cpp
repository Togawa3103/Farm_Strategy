#include "Player.h"
#include<string>
void Player::Update_ResultMenu(int maxGameMode, int* selected_GameMode, int* gameMode) {
	this->input.InitInput();
	this->input.Update_ResultMenu();
	this->Action_ResultMenu(maxGameMode, selected_GameMode, gameMode);
}

void Player::Action_ResultMenu(int maxGameMode, int* selected_GameMode, int* gameMode) {
	if (this->input.keyState[KEY_INPUT_S]) { //キー「S」を押下しているとき
		*selected_GameMode = (*selected_GameMode + 1) % maxGameMode;
	}
	if (this->input.keyState[KEY_INPUT_W]) { //キー「W」を押下しているとき
		*selected_GameMode = (*selected_GameMode + maxGameMode - 1) % maxGameMode;
	}
	if (this->input.keyState[KEY_INPUT_RETURN]) { //キー「RETURN」を押下しているとき
		*gameMode = *selected_GameMode;
	}
}

void Player::DrawResult() {
	DrawBox(350, 50, 450, 100, this->color_white, TRUE);
	DrawBox(355, 55, 445, 95, this->color_black, TRUE);
	DrawFormatString(360, 70, this->color_white, std::to_string(score).c_str());
}