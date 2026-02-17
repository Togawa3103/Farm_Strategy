#include"Game.h"

void Game::Update_ResultMenu(int* selected_GameMode, int* gameMode) {
	this->player.Update_ResultMenu(ResultMenu_Max, selected_GameMode, gameMode);
}

void Game::Game_ResultLoop() {
	unsigned int Comand_Cr1 = GetColor(255, 255, 255);
	unsigned int Comand_Cr2 = GetColor(0, 0, 0);
	int gameMode = -1;
	//this->gameMode = -1;
	int selected_GameMode = 0;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		this->Update_ResultMenu(&selected_GameMode, &(gameMode)); //状態の更新
		this->DrawResult(Comand_Cr1, Comand_Cr2, selected_GameMode);

		now = clock();
		looptime = now - end;
		if (looptime < mfps) {
			Sleep(mfps - looptime);
		}
		end = now;

		if (gameMode > -1) {
			this->gameMode = gameMode;
			break;
		}
	}
}

void Game::DrawResult(unsigned int Color1, unsigned int Color2, int selectedMenu) {
	this->DrawResultMenu(Color1, Color2, selectedMenu);
	this->player.DrawResult();
}

void Game::DrawResultMenu(unsigned int Color1, unsigned int Color2, int selectedMenu) {
	//外枠の表示
	DrawBox(340, 370, 460, 500, Color1, TRUE);
	DrawBox(345, 375, 455, 495, Color2, TRUE);
	
	//外枠の表示
	DrawBox(340, 270, 460, 320, Color1, TRUE);
	DrawBox(345, 275, 455, 315, Color2, TRUE);
	if (this->gameMode== StartMenu_VS) {
		if (this->player.score > this->npc.score) {
			DrawFormatString(360, 285 , Color1, "勝ち！");
		}
		else if(this->player.score < this->npc.score){
			DrawFormatString(360, 285, Color1, "負け！");
		}
		else if (this->player.score == this->npc.score) {
			DrawFormatString(360, 285, Color1, "引き分け！");
		}
	}
	//選択肢の表示
	for (int i = 0; i < ResultMenu_Max; i++) {
		if (selectedMenu == i) {
			DrawBox(355, 385 + 40 * i, 445, 425 + 40 * i, Color1, TRUE);
			DrawFormatString(360, 390 + 45 * i, Color2, result[i].menu_name);
		}
		else {
			DrawFormatString(360, 390 + 45 * i, Color1, result[i].menu_name);
		}
	}
}

