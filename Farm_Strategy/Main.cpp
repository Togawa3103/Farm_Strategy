#include "DxLib.h"
#include "Game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game game; //ゲームインスタンス生成
	while (true) {
		game.Game_StartLoop(); //スタート画面のループ開始
		if (game.gameMode ==StartMenu_End) {
			break;
		}
		game.Game_MainLoop(); //ゲームメインループ開始
		game.Game_ResultLoop(); //リザルト画面のループ開始
		if (game.gameMode == ResultMenu_End) {
			break;
		}
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}