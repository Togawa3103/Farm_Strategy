#pragma once
#include"Input_NPC.h"
#include"Tool.h"

void InputNPC::Update(int toolNum, int cropNum, int score, int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData) {
	memset(this->keyState, 0, sizeof(char) * 256);
	this->Agent(toolNum,cropNum,score,x,y,map,cropVec,cropData,toolData);
	if (this->frame > 0) {
		this->keyState[KEY_INPUT_E] = 0;
		this->keyState[KEY_INPUT_Q] = 0;
		this->keyState[KEY_INPUT_Z] = 0;

		//this->keyState[KEY_INPUT_SPACE] = 0;
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_E]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_Q]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_Z]) {
		this->frame++;
	}
	/*else if (toolNum == 1 && this->keyState[KEY_INPUT_SPACE]) {
		this->frame++;
	}*/
}

void InputNPC::Agent(int toolNum, int cropNum, int score, int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData) {
	//this->cropGrownVec[]
	/*int random_number = rd() % 120;
	if (random_number>=0&&random_number<15) {
		this->keyState[KEY_INPUT_E] = 1;
	}
	if (random_number >= 15 && random_number < 30) {
		this->keyState[KEY_INPUT_Q] = 1;
	}
	if (random_number >= 30 && random_number < 45) {
		this->keyState[KEY_INPUT_Z] = 1;
	}
	if (random_number >= 45 && random_number < 60) {
		this->keyState[KEY_INPUT_W] = 1;
	}
	if (random_number >= 60 && random_number < 75) {
		this->keyState[KEY_INPUT_A] = 1;
	}
	if (random_number >= 75 && random_number < 90) {
		this->keyState[KEY_INPUT_S] = 1;
	}
	if (random_number >= 90 && random_number < 105) {
		this->keyState[KEY_INPUT_D] = 1;
	}
	if (random_number >= 105 && random_number < 120) {
		this->keyState[KEY_INPUT_SPACE] = 1;
	}*/
	//マップ上の今いるところに作物がない場合
	/*switch (map[x / MAP_SELL_LENGTH][y / MAP_SELL_LENGTH])
	{
	case(0):
		if (toolNum == Tool_InputNPC_Hoe) {
			this->keyState[KEY_INPUT_SPACE] = 1;
		}
		else {
			this->keyState[KEY_INPUT_E] = 1;
		}
		break;
	case(1):
	{
		std::vector<std::vector<int>> vec = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };
		int x_1y_1 = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
		int xy_1 = (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
		int x1y_1 = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
		int x_1y = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH);
		int x1y = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH);
		int x_1y1 = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
		int xy1 = (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
		int x1y1 = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
		std::vector<int> diff = { x_1y_1, xy_1, x1y_1, x_1y, x1y, x_1y1, xy1, x1y1 };
		int minDiff = 0;
		for (int i = 1; i < diff.size() - 1; i++) {
			if (map[x / MAP_SELL_LENGTH + vec[i][0]][y / MAP_SELL_LENGTH + vec[i][1]] == 0) {
				if (diff[minDiff] > diff[i]) {
					minDiff = i;
				}
			}
		}
		switch (minDiff) {
		case 0:
			this->keyState[KEY_INPUT_A] = 1;
			this->keyState[KEY_INPUT_W] = 1;
			break;
		case 1:
			this->keyState[KEY_INPUT_W] = 1;
			break;
		case 2:
			this->keyState[KEY_INPUT_D] = 1;
			this->keyState[KEY_INPUT_W] = 1;
			break;
		case 3:
			this->keyState[KEY_INPUT_A] = 1;
			break;
		case 4:
			this->keyState[KEY_INPUT_D] = 1;
			break;
		case 5:
			this->keyState[KEY_INPUT_A] = 1;
			this->keyState[KEY_INPUT_S] = 1;
			break;
		case 6:
			this->keyState[KEY_INPUT_S] = 1;
			break;
		case 7:
			this->keyState[KEY_INPUT_S] = 1;
			this->keyState[KEY_INPUT_D] = 1;
			break;
		}
	}
		break;

	case(2):
	{
		if ((*cropVec).size()<10) {
			if (toolNum == Tool_InputNPC_Scissors) {
				this->keyState[KEY_INPUT_SPACE] = 1;
			}
			else {
				this->keyState[KEY_INPUT_E] = 1;
			}

			std::vector<std::vector<int>> vec = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };
			int x_1y_1 = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
			int xy_1 = (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
			int x1y_1 = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
			int x_1y = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH);
			int x1y = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH);
			int x_1y1 = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
			int xy1 = (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
			int x1y1 = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
			std::vector<int> diff = { x_1y_1, xy_1, x1y_1, x_1y, x1y, x_1y1, xy1, x1y1 };
			int minDiff = 0;
			for (int i = 1; i < diff.size() - 1; i++) {
				if (x / MAP_SELL_LENGTH + vec[i][0] > 0 && x / MAP_SELL_LENGTH + vec[i][0] < WIDTH) {
					if (y / MAP_SELL_LENGTH + vec[i][1] > 0 && y / MAP_SELL_LENGTH + vec[i][1] < HEIGHT) {
						if (map[x / MAP_SELL_LENGTH + vec[i][0]][y / MAP_SELL_LENGTH + vec[i][1]] == 0
							|| (map[x / MAP_SELL_LENGTH + vec[i][0]][y / MAP_SELL_LENGTH + vec[i][1]] == 2 && this->SearchGrownCrop(cropVec, x / MAP_SELL_LENGTH + vec[i][0], y / MAP_SELL_LENGTH + vec[i][1]))) {
							if (diff[minDiff] > diff[i]) {
								minDiff = i;
							}
						}
					}
				}
			}
			switch (minDiff) {
			case 0:
				this->keyState[KEY_INPUT_A] = 1;
				this->keyState[KEY_INPUT_W] = 1;
				break;
			case 1:
				this->keyState[KEY_INPUT_W] = 1;
				break;
			case 2:
				this->keyState[KEY_INPUT_D] = 1;
				this->keyState[KEY_INPUT_W] = 1;
				break;
			case 3:
				this->keyState[KEY_INPUT_A] = 1;
				break;
			case 4:
				this->keyState[KEY_INPUT_D] = 1;
				break;
			case 5:
				this->keyState[KEY_INPUT_A] = 1;
				this->keyState[KEY_INPUT_S] = 1;
				break;
			case 6:
				this->keyState[KEY_INPUT_S] = 1;
				break;
			case 7:
				this->keyState[KEY_INPUT_S] = 1;
				this->keyState[KEY_INPUT_D] = 1;
				break;
			}
		}
		else {
			if (toolNum == Tool_InputNPC_Scissors) {
				this->keyState[KEY_INPUT_SPACE] = 1;
			}
			else {
				this->keyState[KEY_INPUT_E] = 1;
			}

			std::vector<std::vector<int>> vec = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };
			int x_1y_1 = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
			int xy_1 = (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
			int x1y_1 = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
			int x_1y = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH);
			int x1y = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH);
			int x_1y1 = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
			int xy1 = (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
			int x1y1 = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
				+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
			std::vector<int> diff = { x_1y_1, xy_1, x1y_1, x_1y, x1y, x_1y1, xy1, x1y1 };
			int minDiff = 0;
			for (int i = 1; i < diff.size() - 1; i++) {
				if (x / MAP_SELL_LENGTH + vec[i][0] > 0 && x / MAP_SELL_LENGTH + vec[i][0] < WIDTH) {
					if (y / MAP_SELL_LENGTH + vec[i][1] > 0 && y / MAP_SELL_LENGTH + vec[i][1] < HEIGHT) {
						if (map[x / MAP_SELL_LENGTH + vec[i][0]][y / MAP_SELL_LENGTH + vec[i][1]] == 0
							|| (map[x / MAP_SELL_LENGTH + vec[i][0]][y / MAP_SELL_LENGTH + vec[i][1]] == 2 && this->SearchGrownCrop(cropVec, x / MAP_SELL_LENGTH + vec[i][0], y / MAP_SELL_LENGTH + vec[i][1]))) {
							if (diff[minDiff] > diff[i]) {
								minDiff = i;
							}
						}
					}
				}
			}
			switch (minDiff) {
			case 0:
				this->keyState[KEY_INPUT_A] = 1;
				this->keyState[KEY_INPUT_W] = 1;
				break;
			case 1:
				this->keyState[KEY_INPUT_W] = 1;
				break;
			case 2:
				this->keyState[KEY_INPUT_D] = 1;
				this->keyState[KEY_INPUT_W] = 1;
				break;
			case 3:
				this->keyState[KEY_INPUT_A] = 1;
				break;
			case 4:
				this->keyState[KEY_INPUT_D] = 1;
				break;
			case 5:
				this->keyState[KEY_INPUT_A] = 1;
				this->keyState[KEY_INPUT_S] = 1;
				break;
			case 6:
				this->keyState[KEY_INPUT_S] = 1;
				break;
			case 7:
				this->keyState[KEY_INPUT_S] = 1;
				this->keyState[KEY_INPUT_D] = 1;
				break;
			}
		}
	}
	break;
	}*/

	//作物の変更
	int nextCropNum = (cropNum + 1) % (*cropData).size();
	if (((*cropData)[nextCropNum].cost<score&& (*cropData)[nextCropNum].cost >(*cropData)[cropNum].cost)|| (*cropData)[cropNum].cost > score) {
		this->keyState[KEY_INPUT_Q] = 1;
	}

	//ツールのアップグレード
	if ((*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].upgrade_cost<score) {
		this->keyState[KEY_INPUT_Z] = 1;
		//toolNum = toolNum + 1;
	}

	int count = 0;
	for (int i = 0; i < (*cropVec).size(); i++) {
		if (map[(*cropVec)[i].x][(*cropVec)[i].y]==2) {
			count++;
		}
	}
	if(this->cropGrownVec.size()>0){
		int minDiff = 0;
		int diff = 99999999999;
		for (int i = 0; i < this->cropGrownVec.size(); i++) {
			int diff_i = (x / MAP_SELL_LENGTH - this->cropGrownVec[i].x) * (x / MAP_SELL_LENGTH - this->cropGrownVec[i].x)
				+ (y / MAP_SELL_LENGTH - this->cropGrownVec[i].y) * (y / MAP_SELL_LENGTH - this->cropGrownVec[i].y);
			if (diff>diff_i) {
				minDiff = i;
				diff = diff_i;
			}
		}
		if (toolNum == Tool_InputNPC_Scissors) {
			//this->keyState[KEY_INPUT_SPACE] = 1;
		}
		else {
			this->keyState[KEY_INPUT_E] = 1;
		}
		if (x / MAP_SELL_LENGTH > this->cropGrownVec[minDiff].x) {
			this->keyState[KEY_INPUT_A] = 1;
		}else if (x / MAP_SELL_LENGTH < this->cropGrownVec[minDiff].x) {
			this->keyState[KEY_INPUT_D] = 1;
		}
		if (y / MAP_SELL_LENGTH > this->cropGrownVec[minDiff].y) {
			this->keyState[KEY_INPUT_W] = 1;
		}else if (y / MAP_SELL_LENGTH < this->cropGrownVec[minDiff].y) {
			this->keyState[KEY_INPUT_S] = 1;
		}
		
		int canUseInErea=0;
		std::vector<GROWNCROP> erea;
		GROWNCROP tmp_leftX;
		GROWNCROP tmp_rightX;
		GROWNCROP tmp_upY;
		GROWNCROP tmp_downY;
		if ((*toolData)[toolNum].toolLevel > 0) {
			int toolPower = (*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].leftX;
			if(toolPower!=0)if (map[x / MAP_SELL_LENGTH + toolPower][y / MAP_SELL_LENGTH] == (toolNum + 1) / 2 * 2) {
				//canUseInErea += map[x / MAP_SELL_LENGTH + toolPower][y / MAP_SELL_LENGTH] == (toolNum + 1) / 2 * 2;
				tmp_leftX = { x / MAP_SELL_LENGTH + toolPower ,y / MAP_SELL_LENGTH };
				erea.push_back(tmp_leftX);
			}

			toolPower = (*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].rightX;
			if (toolPower != 0)if (map[x / MAP_SELL_LENGTH + toolPower][y / MAP_SELL_LENGTH] == (toolNum + 1) / 2 * 2) {
				//canUseInErea += map[x / MAP_SELL_LENGTH + toolPower][y / MAP_SELL_LENGTH] == (toolNum + 1) / 2 * 2;
				tmp_rightX = { x / MAP_SELL_LENGTH + toolPower ,y / MAP_SELL_LENGTH };
				erea.push_back(tmp_rightX);
			}

			toolPower = (*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].upY;
			if (toolPower != 0)if (map[x / MAP_SELL_LENGTH][y / MAP_SELL_LENGTH + toolPower] == (toolNum + 1) / 2 * 2) {
				//canUseInErea += map[x / MAP_SELL_LENGTH + toolPower][y / MAP_SELL_LENGTH] == (toolNum + 1) / 2 * 2;
				tmp_upY = { x / MAP_SELL_LENGTH,y / MAP_SELL_LENGTH + toolPower };
				erea.push_back(tmp_upY);
			}
			
			toolPower = (*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].downY;
			if (toolPower != 0)if (map[x / MAP_SELL_LENGTH][y / MAP_SELL_LENGTH + toolPower] == (toolNum + 1) / 2 * 2) {
				//canUseInErea += map[x / MAP_SELL_LENGTH + toolPower][y / MAP_SELL_LENGTH] == (toolNum + 1) / 2 * 2;
				tmp_downY = { x / MAP_SELL_LENGTH,y / MAP_SELL_LENGTH + toolPower };
				erea.push_back(tmp_downY);
			}
		}
		if (x / MAP_SELL_LENGTH == this->cropGrownVec[minDiff].x && y / MAP_SELL_LENGTH == this->cropGrownVec[minDiff].y) {
			if (this->SearchGrownCrop(cropVec, this->cropGrownVec[minDiff].x, this->cropGrownVec[minDiff].y)){
				this->keyState[KEY_INPUT_SPACE] = 1;
				this->cropGrownVec.erase(this->cropGrownVec.begin() + minDiff);
				for (int i = 0; i < erea.size(); i++) {
					int ereaX = (erea[i].x);
					int ereaY = (erea[i].y);
					int grownCropNumber = this->getGrownCropNum(&(this->cropGrownVec), ereaX, ereaY);
					if (grownCropNumber >= 0&& this->SearchGrownCrop(cropVec, ereaX, ereaY)) {
						this->keyState[KEY_INPUT_SPACE] = 1;
						//if ((*cropVec).size() != this->cropGrownVec.size()) {
						this->cropGrownVec.erase(this->cropGrownVec.begin() + grownCropNumber);
						//}
					}
				}
			}
		}
	}
	else if (count >=20) {
		for (int i = 0; i < (*cropVec).size(); i++) {
			if(map[(*cropVec)[i].x][(*cropVec)[i].y] == 2)this->cropGrownVec.push_back((*cropVec)[i]);
		}
	}
	else if (count < 20) {
		
		if (toolNum == Tool_InputNPC_Hoe) {
			this->keyState[KEY_INPUT_SPACE] = 1;
		}
		else {
			this->keyState[KEY_INPUT_E] = 1;
		}
		std::vector<std::vector<int>> vec = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };
		int x_1y_1 = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
		int xy_1 = (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
		int x1y_1 = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH);
		int x_1y = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH);
		int x1y = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH) * MAP_SELL_LENGTH);
		int x_1y1 = (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH - 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
		int xy1 = (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
		int x1y1 = (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH)
			+ (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + 1) * MAP_SELL_LENGTH);
		std::vector<int> diff = { x_1y_1, xy_1, x1y_1, x_1y, x1y, x_1y1, xy1, x1y1 };
		int minDiff = 0;
		for (int i = 1; i < diff.size(); i++) {
			if (x / MAP_SELL_LENGTH + vec[i][0] > 0 && x / MAP_SELL_LENGTH + vec[i][0] < WIDTH) {
				if (y / MAP_SELL_LENGTH + vec[i][1] > 0 && y / MAP_SELL_LENGTH + vec[i][1] < HEIGHT) {
					if (map[x / MAP_SELL_LENGTH + vec[i][0]][y / MAP_SELL_LENGTH + vec[i][1]] == 0) {
						if (diff[minDiff] > diff[i]) {
							minDiff = i;
						}
					}
				}
			}
		}
		switch (minDiff) {
		case 0:
			this->keyState[KEY_INPUT_A] = 1;
			this->keyState[KEY_INPUT_W] = 1;
			break;
		case 1:
			this->keyState[KEY_INPUT_W] = 1;
			break;
		case 2:
			this->keyState[KEY_INPUT_D] = 1;
			this->keyState[KEY_INPUT_W] = 1;
			break;
		case 3:
			this->keyState[KEY_INPUT_A] = 1;
			break;
		case 4:
			this->keyState[KEY_INPUT_D] = 1;
			break;
		case 5:
			this->keyState[KEY_INPUT_A] = 1;
			this->keyState[KEY_INPUT_S] = 1;
			break;
		case 6:
			this->keyState[KEY_INPUT_S] = 1;
			break;
		case 7:
			this->keyState[KEY_INPUT_S] = 1;
			this->keyState[KEY_INPUT_D] = 1;
			break;
		}
	}
}

bool InputNPC::SearchGrownCrop(std::vector<CROP>* cropVec, int x, int y) {
	for (int i = (*cropVec).size() - 1; i >= 0; i--) {
		if ((*cropVec)[i].x == x) {
			if ((*cropVec)[i].y == y) {
				if ((*cropVec)[i].cropGrowth == (*cropVec)[i].cropMaxGrowth - 1) {
					return true;
				}
			}
		}
	}
	return false;
}

int InputNPC::getGrownCropNum(std::vector<CROP>* cropVec, int x, int y) {
	for (int i = (*cropVec).size() - 1; i >= 0; i--) {
		if ((*cropVec)[i].x == x) {
			if ((*cropVec)[i].y == y) {
					return i;
			}
		}
	}
	return -1;
}