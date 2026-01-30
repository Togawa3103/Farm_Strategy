#include"Game.h"

void Game::Game_MainLoop() {
	this->map.LoadCropGraph();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		this->Update(); //ó‘Ô‚ÌXV
		this->Draw(); //‰æ–Ê•\Ž¦
		

		now = clock();
		looptime = now - end;
		if (looptime < mfps) {
			Sleep(mfps - looptime);
		}
		end = now;
	}
}