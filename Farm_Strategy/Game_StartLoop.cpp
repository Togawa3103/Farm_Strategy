#include"Game.h"

void Game::Update_StartMenu(int* selected_GameMode, int* gameMode) {
	this->player.Update_StartMenu(StartMenu_Max, selected_GameMode, gameMode);
}

void Game::Game_StartLoop() {
	unsigned int Comand_Cr1 = GetColor(255, 255, 255);
	unsigned int Comand_Cr2 = GetColor(0, 0, 0);

	int selected_GameMode = 0;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		this->Update_StartMenu(&selected_GameMode, &(this->gameMode)); //状態の更新
		this->DrawStartMenu(Comand_Cr1, Comand_Cr2, selected_GameMode);

		now = clock();
		looptime = now - end;
		if (looptime < mfps) {
			Sleep(mfps - looptime);
		}
		end = now;
		if (this->gameMode) {

		}
		if (this->gameMode > -1) {
			break;
		}
	}
}

void Game::DrawStartMenu(unsigned int Color1, unsigned int Color2, int selectedMenu) {
	//外枠の表示
	DrawBox(200, 370, 350, 500, Color1, TRUE);
	DrawBox(210, 380, 340, 490, Color2, TRUE);

	//選択肢の表示
	for (int i = 0; i < StartMenu_Max; i++) {
		if (selectedMenu == i) {
			DrawBox(215, 385 + 40 * i, 335, 425 + 40 * i, Color1, TRUE);
			DrawFormatString(220, 390 + 45 * i, Color2, start[i].startmenu_name);
		}
		else {
			DrawFormatString(220, 390 + 45 * i, Color1, start[i].startmenu_name);
		}
	}
}