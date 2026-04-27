#pragma once
#include"Input_NPC_Learning.h"
#include"Tool.h"
#include"Game_QLearning.h"
#include<random>

InputNPC_Learning::InputNPC_Learning() {
	this->keyState;
	this->frame = 0;
	std::random_device rd{};

	for (int i = 0; i < pattern_hoe.size();i++) {
		this->qVec.push_back(rd() % 100);
	}
	this->action = -1;
}


void InputNPC_Learning::InitCropGrownVec() {
	this->cropGrownVec.clear();
}

void InputNPC_Learning::Update(int time, int toolNum, int cropNum, int score, int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData) {
	memset(this->keyState, 0, sizeof(char) * 256);
	this->Agent(time, toolNum, cropNum, score, x, y, map, cropVec, cropData, toolData);
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
}

void InputNPC_Learning::Agent(int time, int toolNum, int cropNum, int score, int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData) {
	//次の作物のコストが支払える余裕があるとき or 今の作物のコストが払えないとき or 今の作物が時間内に育ち切らないとき、作物の変更を行う
	int nextCropNum = (cropNum + 1) % (*cropData).size();
	if (((*cropData)[nextCropNum].cost + nextCropNum * 0 < score && (*cropData)[nextCropNum].cost > (*cropData)[cropNum].cost && (*cropData)[nextCropNum].growthSpeed / 100 * ((*cropData)[nextCropNum].maxGrowth - 1) < 100 - time) || (*cropData)[cropNum].cost > score || (*cropData)[cropNum].growthSpeed / 100 * ((*cropData)[cropNum].maxGrowth - 1) > 100 - time) {
		this->keyState[KEY_INPUT_Q] = 1;
	}

	//今のツール番号のアップグレードが行えるとき、ツールのアップグレード
	if ((*toolData)[toolNum].toolUpgradeData[(*toolData)[toolNum].toolLevel].upgrade_cost + 300 < score) {
		this->keyState[KEY_INPUT_Z] = 1;
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

	//NPCの作物が(50-経過時間/2)+5個以上になり、収穫予定作物があるとき
	if (this->cropGrownVec.size() > 0) {
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
		else {
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
	else if (count >= (100 - time / 2 + 5) || time > 95) {
		//収穫予定作物を設定
		for (int i = 0; i < (*cropVec).size(); i++) {
			if (map[(*cropVec)[i].x][(*cropVec)[i].y] == 2)this->cropGrownVec.push_back((*cropVec)[i]);
		}
	}

	//NPCの作物が(50-経過時間/2)+5個以下のとき
	else if (count < (100 - time / 2 + 5)) {
		if (toolNum == Tool_InputNPC_Hoe) {
			if (map[x / MAP_SELL_LENGTH][y / MAP_SELL_LENGTH] == 0 && (*cropData)[cropNum].growthSpeed / 100 * ((*cropData)[cropNum].maxGrowth - 1) < 100 - time) {
				this->keyState[KEY_INPUT_SPACE] = 1;
			}
		}
		else {
			this->keyState[KEY_INPUT_E] = 1;
		}

		//actionをリセット
		if (returnXY.x == x / MAP_SELL_LENGTH && returnXY.y < y / MAP_SELL_LENGTH) {
			this->action = -1;
		}
		//Qテーブルからよいアクションを検索
		if(this->action==-1)returnXY = this->selectAction(map, cropVec,x, y);
		
		if (returnXY.x > x / MAP_SELL_LENGTH) {
			this->keyState[KEY_INPUT_D] = 1;
		}
		else if ((returnXY.x < x / MAP_SELL_LENGTH)) {
			this->keyState[KEY_INPUT_A] = 1;
		}
		if (returnXY.y > y / MAP_SELL_LENGTH) {
			this->keyState[KEY_INPUT_S] = 1;
		}
		else if ((returnXY.y < y / MAP_SELL_LENGTH)) {
			this->keyState[KEY_INPUT_W] = 1;
		}
	}
}

bool InputNPC_Learning::SearchGrownCrop(std::vector<CROP>* cropVec, int x, int y) {
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

int InputNPC_Learning::getGrownCropNum(std::vector<CROP>* cropVec, int x, int y) {
	for (int i = (*cropVec).size() - 1; i >= 0; i--) {
		if ((*cropVec)[i].x == x) {
			if ((*cropVec)[i].y == y) {
				return i;
			}
		}
	}
	return -1;
}

COORDINATE InputNPC_Learning::selectAction(int map[][HEIGHT], std::vector<CROP>* cropVec, int x, int y) {
	std::random_device rd{};
	int action = 0;
	int epsilon = 30;

	
	int maxAction = 0;
	float qMax = -99999;
	int jMax = 0;
	std::vector<float> rewardList = this->getRewardList(map,cropVec,x,y);
	while (true) {
		if (epsilon < rd() % 100) {
			for (int i = 0; i < 4; i++) {
				float q = -999999;
				int tmp_j = 0;
				for (int j = 0; j < pattern_hoe.size() / 4; j++) {
					if (rewardList[i] != this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH)
						&& rewardList[i] == pattern_hoe[j]) {
						q = qVec[j + i * pattern_hoe.size() / 4];
						tmp_j = j;
					}
				}
				if (qMax < q) {
					maxAction = i;
					qMax = q;
					jMax = tmp_j;
				}

			}
		}
		else {
			maxAction = rd() % 4;
			for (int i = 0; i < pattern_hoe.size() / 4;i++) {
				if (rewardList[maxAction]==pattern_hoe[i]) {
					qMax = qVec[i + maxAction * pattern_hoe.size() / 4];
					jMax = i;
				}
			}
		}
		
		switch (maxAction) {
		case 0:
			this->returnXY = { x / MAP_SELL_LENGTH ,y / MAP_SELL_LENGTH - 1 };
			break;
		case 1:
			this->returnXY = { x / MAP_SELL_LENGTH ,y / MAP_SELL_LENGTH + 1 };
			break;
		case 2:
			this->returnXY = { x / MAP_SELL_LENGTH + 1,y / MAP_SELL_LENGTH };
			break;
		case 3:
			this->returnXY = { x / MAP_SELL_LENGTH - 1  ,y / MAP_SELL_LENGTH };
			break;
		}

		qVec[jMax + maxAction * pattern_hoe.size() / 4] += 0.01 * (rewardList[maxAction] + 0.9 * getMaxNextQ(map, cropVec, this->returnXY.x, this->returnXY.y) - qVec[jMax + maxAction * pattern_hoe.size() / 4]);
		//qVec[jMax + maxAction * pattern_hoe.size() / 4] += 0.1 * (rewardList[maxAction] + 0.1 * qMax);

		if (this->returnXY.x>=0&& this->returnXY.x < WIDTH
			&& this->returnXY.y >= 0 && this->returnXY.y < HEIGHT) {
			break;
		}
	}
	
	return returnXY;
}

float InputNPC_Learning::getReward(int map[][HEIGHT], std::vector<CROP>* cropVec,int x, int y) {
	float reward = 0;
	if (map[x][y] == 0) {
		reward += 100;
	}
	if (map[x][y] == 2&& this->SearchGrownCrop(cropVec, x, y)) {
		reward -= 5;
	}
	if (map[x][y] == 2) {
		reward -= 5;
	}
	if (map[x][y] == 1) {
		reward -= 100;
	}
	return reward;
}

std::vector<float> InputNPC_Learning::getRewardList(int map[][HEIGHT], std::vector<CROP>* cropVec, int x, int y) {
	float up = 0;
	float down = 0;
	float right = 0;
	float left = 0;

	up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH);
	if (x / MAP_SELL_LENGTH - 1 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH - 1);
	}
	else {
		up -= 100;
	}
	if (x / MAP_SELL_LENGTH + 1 < WIDTH) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH - 1);
	}
	else {
		up -= 100;
	}
	if (y / MAP_SELL_LENGTH - 1 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH - 1);
	}
	else {
		up -= 100;
	}
	if (y / MAP_SELL_LENGTH - 2 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH - 2);
	}
	else {
		up -= 100;
	}
	if (y / MAP_SELL_LENGTH - 3 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH - 3);
	}
	else {
		up -= 100;
	}
	if (y / MAP_SELL_LENGTH - 4 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH - 4);
	}
	else {
		up -= 100;
	}
	if (y / MAP_SELL_LENGTH - 3 > 0&& x / MAP_SELL_LENGTH - 1 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH - 3);
	}
	else {
		up -= 100;
	}
	if (y / MAP_SELL_LENGTH - 2 > 0 && x / MAP_SELL_LENGTH - 1 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH - 2);
	}
	else {
		up -= 100;
	}
	if (y / MAP_SELL_LENGTH - 3 > 0 && x / MAP_SELL_LENGTH + 1 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH - 3);
	}
	else {
		up -= 100;
	}
	if (x / MAP_SELL_LENGTH + 1 > 0 && y / MAP_SELL_LENGTH - 2 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH - 2);
	}
	else {
		up -= 100;
	}
	if (x / MAP_SELL_LENGTH - 2 > 0 && y / MAP_SELL_LENGTH - 1 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 2, y / MAP_SELL_LENGTH - 1);
	}
	else {
		up -= 100;
	}
	if (x / MAP_SELL_LENGTH + 2 > 0 && y / MAP_SELL_LENGTH - 1 > 0) {
		up += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 2, y / MAP_SELL_LENGTH - 1);
	}
	else {
		up -= 100;
	}

	down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH);
	if (x / MAP_SELL_LENGTH - 1 > 0) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH + 1);
	}
	else {
		down -= 100;
	}
	if (x / MAP_SELL_LENGTH + 1 < WIDTH) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH + 1);
	}
	else {
		down -= 100;
	}
	if (y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH + 1);
	}
	else {
		down -= 100;
	}
	if (y / MAP_SELL_LENGTH + 2 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH + 2);
	}
	else {
		down -= 100;
	}
	if (y / MAP_SELL_LENGTH + 3 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH + 3);
	}
	else {
		down -= 100;
	}
	if (y / MAP_SELL_LENGTH + 4 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH + 4);
	}
	else {
		down -= 100;
	}
	if (x / MAP_SELL_LENGTH + 1 < WIDTH && y / MAP_SELL_LENGTH + 2 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH + 2);
	}
	else {
		down -= 100;
	}
	if (x / MAP_SELL_LENGTH + 1 < WIDTH && y / MAP_SELL_LENGTH + 3 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH + 3);
	}
	else {
		down -= 100;
	}
	if (x / MAP_SELL_LENGTH -1 > 0 && y / MAP_SELL_LENGTH + 2 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH + 2);
	}
	else {
		down -= 100;
	}
	if (x / MAP_SELL_LENGTH - 1 > 0 && y / MAP_SELL_LENGTH + 3 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH + 3);
	}
	else {
		down -= 100;
	}
	if (x / MAP_SELL_LENGTH - 2 > 0 && y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 2, y / MAP_SELL_LENGTH + 1);
	}
	else {
		down -= 100;
	}
	if (x / MAP_SELL_LENGTH + 2 < WIDTH && y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		down += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 2, y / MAP_SELL_LENGTH + 1);
	}
	else {
		down -= 100;
	}


	right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH);
	if (x / MAP_SELL_LENGTH + 1 < WIDTH) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 2 < WIDTH) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 2, y / MAP_SELL_LENGTH);
	}
	else {
		right -= 100;
	}
	if (y / MAP_SELL_LENGTH - 1 > 0) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH - 1);
	}
	else {
		right -= 100;
	}
	if (y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH + 1);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 3 < WIDTH) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 4, y / MAP_SELL_LENGTH);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 4 < WIDTH) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 4, y / MAP_SELL_LENGTH);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 3 < WIDTH && y / MAP_SELL_LENGTH - 1 > 0) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 3, y / MAP_SELL_LENGTH - 1);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 2 < WIDTH && y / MAP_SELL_LENGTH - 1 > 0) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 2, y / MAP_SELL_LENGTH - 1);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 3 < WIDTH && y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 3, y / MAP_SELL_LENGTH + 1);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 2 < WIDTH && y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 2, y / MAP_SELL_LENGTH + 1);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 1 < WIDTH && y / MAP_SELL_LENGTH - 2 > WIDTH) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH - 2);
	}
	else {
		right -= 100;
	}
	if (x / MAP_SELL_LENGTH + 1 < WIDTH && y / MAP_SELL_LENGTH + 2 < HEIGHT) {
		right += this->getReward(map, cropVec, x / MAP_SELL_LENGTH + 1, y / MAP_SELL_LENGTH + 2);
	}
	else {
		right -= 100;
	}

	left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH, y / MAP_SELL_LENGTH);
	if (x / MAP_SELL_LENGTH - 1 > 0) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 2 > 0) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 2, y / MAP_SELL_LENGTH);
	}
	else {
		left -= 100;
	}
	if (y / MAP_SELL_LENGTH - 1 > 0) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH - 1);
	}
	else {
		left -= 100;
	}
	if (y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH + 1);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 3 > 0) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 3, y / MAP_SELL_LENGTH);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 4 > 0) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 4, y / MAP_SELL_LENGTH);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 2 > 0 && y / MAP_SELL_LENGTH - 1 > 0) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 2, y / MAP_SELL_LENGTH - 1);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 3 > 0 && y / MAP_SELL_LENGTH - 1 > 0) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 3, y / MAP_SELL_LENGTH - 1);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 2 > 0 && y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 2, y / MAP_SELL_LENGTH + 1);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 3 > 0 && y / MAP_SELL_LENGTH + 1 < HEIGHT) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 3, y / MAP_SELL_LENGTH + 1);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 1 > 0 && y / MAP_SELL_LENGTH - 2 >  0) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH - 2);
	}
	else {
		left -= 100;
	}
	if (x / MAP_SELL_LENGTH - 1 > 0 && y / MAP_SELL_LENGTH + 2 < HEIGHT) {
		left += this->getReward(map, cropVec, x / MAP_SELL_LENGTH - 1, y / MAP_SELL_LENGTH + 2);
	}
	else {
		left -= 100;
	}

	
	return { up,down,right,left };
}

float InputNPC_Learning::getMaxNextQ(int map[][HEIGHT], std::vector<CROP>* cropVec, int x, int y) {
	std::vector<float> rewardList = this->getRewardList(map, cropVec, x, y);
	
	float maxQ = -999999999;
	int pattern_hoeNum = 0;
	for (int i = 0;i < pattern_hoe.size() / 4; i++) {
		if (pattern_hoe[i] == rewardList[i]) {
			pattern_hoeNum = i;
			break;
		}
	}
	for (int i = 0; i < 4;i++) {
		if (maxQ < qVec[pattern_hoeNum + i * pattern_hoe.size() / 4]) {
			maxQ = qVec[pattern_hoeNum + i * pattern_hoe.size() / 4];
		}
	}
	return maxQ;
}
