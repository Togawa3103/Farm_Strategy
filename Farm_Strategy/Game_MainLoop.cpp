#include"Game.h"

void Game::Game_MainLoop() {
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		GetHitKeyStateAll(input.keyState);
		this->Update();
		DrawPixel(320, 240 + player.t, GetColor(255, 255, 255));	// “_‚ð‘Å‚Â
	}
}