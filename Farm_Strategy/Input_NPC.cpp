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
	//次の作物のコストが支払えるとき、作物の変更を行う
	int nextCropNum = (cropNum + 1) % (*cropData).size();
	if (((*cropData)[nextCropNum].cost<score&& (*cropData)[nextCropNum].cost >(*cropData)[cropNum].cost)|| (*cropData)[cropNum].cost > score) {
		this->keyState[KEY_INPUT_Q] = 1;
	}

	//今のツール番号のアップグレードが行えるとき、ツールのアップグレード
	if ((*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].upgrade_cost<score) {
		this->keyState[KEY_INPUT_Z] = 1;
		//toolNum = toolNum + 1;
	}

	//すべての作物からNPCの作物をカウント
	int count = 0;
	if (this->cropGrownVec.size() == 0) {
		for (int i = 0; i < (*cropVec).size(); i++) {
			if (map[(*cropVec)[i].x][(*cropVec)[i].y] == 2) {
				count++;
			}
		}
	}

	//NPCの作物が20個以上になり、収穫予定作物があるとき
	if(this->cropGrownVec.size()>0){
		int cropVecNum = this->getGrownCropNum(cropVec, this->cropGrownVec[0].x, this->cropGrownVec[0].y);
		//先頭の収穫予定作物が収穫できないとき、じょうろで成長させる
		if ((*cropVec)[cropVecNum].cropGrowth != (*cropVec)[cropVecNum].cropMaxGrowth - 1) {
			if (x / MAP_SELL_LENGTH > this->cropGrownVec[0].x) {
				this->keyState[KEY_INPUT_A] = 1;
			}
			else if (x / MAP_SELL_LENGTH < this->cropGrownVec[0].x) {
				this->keyState[KEY_INPUT_D] = 1;
			}
			if (y / MAP_SELL_LENGTH > this->cropGrownVec[0].y) {
				this->keyState[KEY_INPUT_W] = 1;
			}
			else if (y / MAP_SELL_LENGTH < this->cropGrownVec[0].y) {
				this->keyState[KEY_INPUT_S] = 1;
			}
			if (toolNum == Tool_InputNPC_WateringCan) {
				if (x / MAP_SELL_LENGTH == this->cropGrownVec[0].x && y / MAP_SELL_LENGTH == this->cropGrownVec[0].y) {
					this->keyState[KEY_INPUT_SPACE] = 1;
				}
			}
			else {
				this->keyState[KEY_INPUT_E] = 1;
			}
		}
		//先頭の収穫予定作物が収穫できるとき、収穫を行う
		else{
			int minDiff = 0;
			int diff = 99999999999;
			
			//最も近い作物を探索
			for (int i = 0; i < this->cropGrownVec.size(); i++) {
				int diff_i = (x / MAP_SELL_LENGTH - this->cropGrownVec[i].x) * (x / MAP_SELL_LENGTH - this->cropGrownVec[i].x)
					+ (y / MAP_SELL_LENGTH - this->cropGrownVec[i].y) * (y / MAP_SELL_LENGTH - this->cropGrownVec[i].y);
				if (diff > diff_i) {
					minDiff = i;
					diff = diff_i;
				}
			}
			
			if (x / MAP_SELL_LENGTH > this->cropGrownVec[minDiff].x) {
				this->keyState[KEY_INPUT_A] = 1;
			}
			else if (x / MAP_SELL_LENGTH < this->cropGrownVec[minDiff].x) {
				this->keyState[KEY_INPUT_D] = 1;
			}
			if (y / MAP_SELL_LENGTH > this->cropGrownVec[minDiff].y) {
				this->keyState[KEY_INPUT_W] = 1;
			}
			else if (y / MAP_SELL_LENGTH < this->cropGrownVec[minDiff].y) {
				this->keyState[KEY_INPUT_S] = 1;
			}
			if (toolNum == Tool_InputNPC_Scissors) {
				int canUseInErea = 0;
				std::vector<GROWNCROP> erea;
				GROWNCROP tmp_leftX;
				GROWNCROP tmp_rightX;
				GROWNCROP tmp_upY;
				GROWNCROP tmp_downY;

				//はさみがアップグレードされているとき
				if ((*toolData)[toolNum].toolLevel > 0) {
					
					//左隣の作物が収穫できるとき
					int toolPower = (*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].leftX;
					if (toolPower != 0)if (map[x / MAP_SELL_LENGTH + toolPower][y / MAP_SELL_LENGTH] == (toolNum + 1) / 2 * 2) {
						tmp_leftX = { x / MAP_SELL_LENGTH + toolPower ,y / MAP_SELL_LENGTH };
						erea.push_back(tmp_leftX);
					}

					//右隣の作物が収穫できるとき
					toolPower = (*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].rightX;
					if (toolPower != 0)if (map[x / MAP_SELL_LENGTH + toolPower][y / MAP_SELL_LENGTH] == (toolNum + 1) / 2 * 2) {
						tmp_rightX = { x / MAP_SELL_LENGTH + toolPower ,y / MAP_SELL_LENGTH };
						erea.push_back(tmp_rightX);
					}
					
					//上の作物が収穫できるとき
					toolPower = (*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].upY;
					if (toolPower != 0)if (map[x / MAP_SELL_LENGTH][y / MAP_SELL_LENGTH + toolPower] == (toolNum + 1) / 2 * 2) {
						tmp_upY = { x / MAP_SELL_LENGTH,y / MAP_SELL_LENGTH + toolPower };
						erea.push_back(tmp_upY);
					}

					//下の作物が収穫できるとき
					toolPower = (*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].downY;
					if (toolPower != 0)if (map[x / MAP_SELL_LENGTH][y / MAP_SELL_LENGTH + toolPower] == (toolNum + 1) / 2 * 2) {
						tmp_downY = { x / MAP_SELL_LENGTH,y / MAP_SELL_LENGTH + toolPower };
						erea.push_back(tmp_downY);
					}
				}

				//今いる位置が最も近い収穫予定作物の位置のとき
				if (x / MAP_SELL_LENGTH == this->cropGrownVec[minDiff].x && y / MAP_SELL_LENGTH == this->cropGrownVec[minDiff].y) {
					if (this->SearchGrownCrop(cropVec, this->cropGrownVec[minDiff].x, this->cropGrownVec[minDiff].y)) {
						this->keyState[KEY_INPUT_SPACE] = 1;
						this->cropGrownVec.erase(this->cropGrownVec.begin() + minDiff);
						//はさみのアップグレードが行われていて、複数の作物を収穫するとき
						for (int i = 0; i < erea.size(); i++) {
							int grownCropNumber = this->getGrownCropNum(&(this->cropGrownVec), erea[i].x, erea[i].y);
							if (grownCropNumber >= 0 && this->SearchGrownCrop(cropVec, erea[i].x, erea[i].y)) {
								this->keyState[KEY_INPUT_SPACE] = 1;
								this->cropGrownVec.erase(this->cropGrownVec.begin() + grownCropNumber);
							}
						}
					}
				}
			}
			else {
				this->keyState[KEY_INPUT_E] = 1;
			}
		}
	}

	//NPCの作物が20個以上になったとき
	else if (count >=20) {
		//収穫予定作物を設定
		for (int i = 0; i < (*cropVec).size(); i++) {
			if(map[(*cropVec)[i].x][(*cropVec)[i].y] == 2)this->cropGrownVec.push_back((*cropVec)[i]);
		}
	}
	
	//NPCの作物が20個以下のとき
	else if (count < 20) {
		
		if (toolNum == Tool_InputNPC_Hoe) {
			if (map[x / MAP_SELL_LENGTH][y / MAP_SELL_LENGTH]==0) {
				this->keyState[KEY_INPUT_SPACE] = 1;
			}
		}
		else {
			this->keyState[KEY_INPUT_E] = 1;
		}

		//最も近い近隣8マスで空いている土地を探す
		int minDiff = 0;
		COORDINATE returnXY;
		returnXY = this->getNeighborhoodFreeSpace(map,x,y);
		if (returnXY.x > x/ MAP_SELL_LENGTH) {
			this->keyState[KEY_INPUT_D] = 1;
		}
		else if((returnXY.x < x / MAP_SELL_LENGTH)){
			this->keyState[KEY_INPUT_A] = 1;
		}
		if (returnXY.y > y / MAP_SELL_LENGTH) {
			this->keyState[KEY_INPUT_S] = 1;
		}
		else if ((returnXY.y < y / MAP_SELL_LENGTH)) {
			this->keyState[KEY_INPUT_W] = 1;
		}
		/*
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
		*/
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

COORDINATE InputNPC::getNeighborhoodFreeSpace(int map[][HEIGHT], int x, int y) {
	std::vector<int> diff;
	std::vector<std::vector<int>> vec;
	
	int minDiff = 0;
	bool couldSearch = false;

	COORDINATE returnXY;
	if (!couldSearch) {
		int count = 1;
		while (count<WIDTH) {
			diff = { 999999999};
			vec = {};
			for (int i = -1*count; i <= 1 * count;i++) {
				for (int j = -1 * count; j <= 1 * count; j++) {
					if (x / MAP_SELL_LENGTH + i > 0 && x / MAP_SELL_LENGTH + i < WIDTH) {
						if (y / MAP_SELL_LENGTH + j > 0 && y / MAP_SELL_LENGTH + j < HEIGHT) {
							if (map[x / MAP_SELL_LENGTH + i][y / MAP_SELL_LENGTH + j] == 0) {
								int diff_length = (x - (x / MAP_SELL_LENGTH + i) * MAP_SELL_LENGTH) * (x - (x / MAP_SELL_LENGTH + i) * MAP_SELL_LENGTH)
									+ (y - (y / MAP_SELL_LENGTH + j) * MAP_SELL_LENGTH) * (y - (y / MAP_SELL_LENGTH + j) * MAP_SELL_LENGTH);
								diff.push_back(diff_length);
								vec.push_back({ x / MAP_SELL_LENGTH + i, y / MAP_SELL_LENGTH + j });
							}
						}
					}
				}
			}
			for (int i = 1; i < diff.size(); i++) {
				if (diff[minDiff] > diff[i]) {
					minDiff = i;
					couldSearch = true;
				}
			}
			if (couldSearch) {
				returnXY.x = vec[minDiff-1][0];
				returnXY.y = vec[minDiff-1][1];
				break;
			}
			count++;
		}
	}
	if (!couldSearch) {
		returnXY.x = 0;
		returnXY.y = 0;
	}
	return returnXY;
}