#include"Game.h"
#include <fstream>

void Game::Game_LearningLoop() {
	std::ifstream infile("output.txt");  // 読み込むファイルのパスを指定
	std::string line;
	int count = 0;
	while (std::getline(infile, line)) {  // 1行ずつ読み込む
		this->npc1.inputNPC.qVec[count] = std::stof(line);
		count++;
	}

	infile.close();
	
	for (int i = 0; i <= 50;i++) {
		this->Init_Learning();
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			this->Update_Learning(); //状態の更新
			//if(i==0||i==50)this->Draw_Learning(); //画面表示
			this->Draw_Learning(); //画面表示

			if (this->time.time > this->time.endTime) {
				break;
			}
		}
		std::ofstream outfile("output.txt");
		for (int i = 0; i < this->npc1.inputNPC.qVec.size(); i++) {
			outfile << this->npc1.inputNPC.qVec[i] << std::endl;
		}
		outfile.close();
	}
	
}