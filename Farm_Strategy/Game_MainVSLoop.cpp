#include"Game.h"

void Game::Game_MainVSLoop() {
	this->Init();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		this->Update_VS(); //ó‘Ô‚ÌXV
		this->Draw_VS(); //‰æ–Ê•\Ž¦


		now = clock();
		looptime = now - end;
		if (looptime < mfps) {
			Sleep(mfps - looptime);
		}
		end = now;

		if (this->time.time > this->time.endTime) {
			break;
		}
	}
}