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

void Player::DrawResult(int x, int y) {
	DrawBox(x, y, x+100, y+50, this->color_white, TRUE);
	DrawBox(x+5, y+5, x+95, y+45, this->color_black, TRUE);
	DrawFormatString(x+10, y+20, this->color_white, std::to_string(this->score).c_str());
}