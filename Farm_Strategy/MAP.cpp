#include"MAP.h"
#include"Crop_PicData.h"

MAP::MAP() {
	this->color_white = GetColor(255, 255, 255);
	this->color_black = GetColor(0, 0, 0);
	this->color_red = GetColor(255, 0, 0);

	//mapの初期化
	for (int i = 0; i < WIDTH;i++) {
		for (int j = 0; j < HEIGHT;j++) {
			this->map[i][j] = 0;
		}
	}
	
	this->cropVec.clear();
	for (int i = 0; i < crop_PicData.size(); i++) {
		for (int j = 0; j < crop_PicData[i].maxGrowth;j++) {
			Animation anima;
			this->animaVec.push_back(anima);
		}
	}
	this->maxCropNum = crop_PicData.size();
}

MAP::~MAP() {}

void MAP::InitMAP() {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			this->map[i][j] = 0;
		}
	}
	this->cropVec = {};
}

void MAP::Update(int* playerScore,std::vector<RETURN_DATA>& dataVec) {
	for (int i = 0; i < dataVec.size();i++) {
		this->GetMAPChangeData(playerScore,&dataVec[i]);
	}
	this->UpdateCROP();
}

void MAP::DrawMAP() {
	DrawBox(MAPBG_START_WIDTH, MAPBG_START_HEIGHT, MAPBG_END_WIDTH, MAPBG_END_HEIGHT, this->color_white, TRUE);
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * i, MAPW_START_HEIGHT + MAP_SELL_LENGTH * j,
					MAPW_END_WIDTH + MAP_SELL_LENGTH * i, MAPW_END_HEIGHT + MAP_SELL_LENGTH * j, this->color_white, TRUE);
		
			switch (this->map[i][j]) {
			case 0:
				DrawBox(MAPB_START_WIDTH + MAP_SELL_LENGTH * i, MAPB_START_HEIGHT + MAP_SELL_LENGTH * j,
					MAPB_END_WIDTH + MAP_SELL_LENGTH * i, MAPB_END_HEIGHT + MAP_SELL_LENGTH * j, this->color_black, TRUE);
				break;
			}
		}
	}
	if (this->cropVec.size()>0) {
		for (int i = 0; i < this->cropVec.size(); i++) {
			this->cropVec[i].DrawCrop(MAPB_START_WIDTH + MAP_SELL_LENGTH * this->cropVec[i].x,
				MAPB_START_HEIGHT + MAP_SELL_LENGTH * this->cropVec[i].y,
				MAPB_END_WIDTH + MAP_SELL_LENGTH * this->cropVec[i].x,
				MAPB_END_HEIGHT + MAP_SELL_LENGTH * this->cropVec[i].y);
		}
	}
}

void MAP::DrawNumCrop(int cropNum) {
	DrawBox(0, 100, 50, 140, this->color_white, TRUE);
	DrawBox(5, 95, 45, 135, this->color_black, TRUE);
	crop_PicData[cropNum].AnimaVec[crop_PicData[cropNum].maxGrowth - 1].DrawAnima(5, 95, 45, 135);
}

void MAP::DrawNPCNumCrop(int cropNum) {
	DrawBox(700, 100, 750, 140, this->color_white, TRUE);
	DrawBox(705, 95, 745, 135, this->color_black, TRUE);
	crop_PicData[cropNum].AnimaVec[crop_PicData[cropNum].maxGrowth - 1].DrawAnima(705, 95, 745, 135);
}

void MAP::GetMAPChangeData(int *playerScore,RETURN_DATA *data) {
	if ((*data).x >= 0 && (*data).y >= 0) {
		switch ((*data).actionFlag) {
		//スペースキーが押されたとき
		case Action_SPACE: 
			switch ((*data).toolNum) {
				//ツールが"くわ"のとき
			case 0:
				switch (this->map[(*data).x][(*data).y]) {
					//農地に作物がないとき
				case 0:
				{
					int cropNum = (*data).cropNum;
					int cost = crop_PicData[cropNum].cost;
					if ((*playerScore) >= cost) {
						//マップの更新
						this->map[(*data).x][(*data).y] = (*data).playerNum;
						
						//作物の作成
						CROP crop((*data).x, (*data).y, cropNum, crop_PicData[cropNum].maxGrowth, crop_PicData[cropNum].score, crop_PicData[cropNum].cropPicDataVec[cropNum].cropPicHandle);
						int count = 0;
						crop.anima = crop_PicData[cropNum].AnimaVec;
						this->cropVec.push_back(crop);

						//コストの支払い
						if(cost>0)*playerScore -= crop_PicData[cropNum].cost;
						
						//SE再生
						this->sound.PlayBGMSound(se[SE_HOE].seSoundHandle);
					}
					break;
				}
				//農地に作物があるとき
				case 1:
					break;
				}
				break;
				//ツールが"じょうろ"のとき
			case 1:
				for (int i = this->cropVec.size() - 1; i >= 0; i--) {
					if (this->cropVec[i].x == (*data).x) {
						if (this->cropVec[i].y == (*data).y) {
							if (this->map[(*data).x][(*data).y] == (*data).playerNum) {
								//作物の成長度を加算
								this->cropVec[i].time = this->cropVec[i].time + 20;

								//SE再生
								this->sound.PlayBGMSound(se[SE_WATERCAN].seSoundHandle);
							}
						}
					}
				}
				break;
				//ツールが"ハサミ"のとき
			case 2:
				if (this->map[(*data).x][(*data).y] == (*data).playerNum) {
					//作物の採取
					*playerScore += ReturnScore((*data).x, (*data).y);
					this->DeleteCROP((*data).x, (*data).y);
					
					//SE再生
					this->sound.PlayBGMSound(se[SE_SCISSORS].seSoundHandle);
					break;
				}
			}
			break;
		}
		
	}
}
			
void MAP::UpdateCROP() {
	for (int i = 0; i < this->cropVec.size(); i++) {
		this->cropVec[i].Update(crop_PicData[this->cropVec[i].cropNum].growthSpeed);
		this->cropVec[i].GrowUp(crop_PicData[this->cropVec[i].cropNum].cropPicDataVec[this->cropVec[i].cropGrowth].cropPicHandle);
	}
}

void MAP::DeleteCROP(int x, int y) {
	for (int i = this->cropVec.size() - 1; i >= 0; i--) {
		if (this->cropVec[i].x == x) {
			if (this->cropVec[i].y == y) {
				this->map[this->cropVec[i].x][this->cropVec[i].y] = 0;
				this->cropVec.erase(this->cropVec.begin() + i);
			}
		}
	}
}

void MAP::LoadCropGraph() {
	for (int i = 0; i < crop_PicData.size(); i++) {
		std::vector<Animation> anima(crop_PicData[i].maxGrowth);
		for (int j = 0; j < crop_PicData[i].cropPicDataVec.size(); j++) {
			crop_PicData[i].cropPicDataVec[j].cropPicHandle = LoadGraph(crop_PicData[i].cropPicDataVec[j].cropPicName);
			ANIMATION_DATA animaData = { crop_PicData[i].cropPicDataVec[j].startFrame, crop_PicData[i].cropPicDataVec[j].endFrame,
				crop_PicData[i].cropPicDataVec[j].cropPicHandle };
			anima[crop_PicData[i].cropPicDataVec[j].cropGrow].anima.push_back(animaData);
		}
		crop_PicData[i].AnimaVec = anima;
	}
}

int MAP::ReturnScore(int x,int y) {
	for (int i = this->cropVec.size() - 1; i >= 0; i--) {
		if (this->cropVec[i].x == x) {
			if (this->cropVec[i].y == y) {
				if (this->cropVec[i].cropGrowth == this->cropVec[i].cropMaxGrowth - 1) {
					return this->cropVec[i].score;
				}
			}
		}
	}
	return 0;
}