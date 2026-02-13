#include "Player.h"

void Player::Update_StartMenu(int maxGameMode, int * selected_GameMode,int*gameMode) {
	this->input.InitInput(); 
	this->input.Update_StartMenu();
	this->Action_StartMenu(maxGameMode,selected_GameMode,gameMode);
}

void Player::Action_StartMenu(int maxGameMode, int* selected_GameMode, int* gameMode) {
	if (this->input.keyState[KEY_INPUT_W]) { //キー「D」を押下しているとき
		*selected_GameMode = (*selected_GameMode + 1) % maxGameMode;
	}
	if (this->input.keyState[KEY_INPUT_S]) { //キー「A」を押下しているとき
		*selected_GameMode = (*selected_GameMode + maxGameMode - 1) % maxGameMode;
	}
	if (this->input.keyState[KEY_INPUT_RETURN]) { //キー「A」を押下しているとき
		*gameMode = *selected_GameMode;
	}
}