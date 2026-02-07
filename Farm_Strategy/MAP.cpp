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
		//std::vector<ANIMATION_DATA> anima(crop_PicData[i].maxGrowth);
		//this->animaVec(crop_PicData[i].maxGrowth);
		for (int j = 0; j < crop_PicData[i].maxGrowth;j++) {
			Animation anima;
			this->animaVec.push_back(anima);
		}
	}
	//this->score = 0;
	this->maxCropNum = crop_PicData.size();
}

MAP::~MAP() {}

void MAP::Update(int* playerScore,std::vector<RETURN_DATA>& dataVec) {
	//this->score = 0;
	//this->cost = 0;
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
			//case 1:
			//	DrawBox(MAPB_START_WIDTH + MAP_SELL_LENGTH * i, MAPB_START_HEIGHT + MAP_SELL_LENGTH * j,
			//		MAPB_END_WIDTH + MAP_SELL_LENGTH * i, MAPB_END_HEIGHT + MAP_SELL_LENGTH * j, this->color_red, TRUE);
			//	break;
			case 0:
				DrawBox(MAPB_START_WIDTH + MAP_SELL_LENGTH * i, MAPB_START_HEIGHT + MAP_SELL_LENGTH * j,
					MAPB_END_WIDTH + MAP_SELL_LENGTH * i, MAPB_END_HEIGHT + MAP_SELL_LENGTH * j, this->color_black, TRUE);
				break;
			}
		}
	}
	if (this->cropVec.size()>0) {
		for (int i = 0; i < this->cropVec.size(); i++) {
			//DrawExtendGraph(MAPB_START_WIDTH + MAP_SELL_LENGTH * this->cropVec[i].x, MAPB_START_HEIGHT + MAP_SELL_LENGTH * this->cropVec[i].y,
			//		MAPB_END_WIDTH + MAP_SELL_LENGTH * this->cropVec[i].x, MAPB_END_HEIGHT + MAP_SELL_LENGTH * this->cropVec[i].y,
			//		this->cropVec[i].cropPicHandle, TRUE);
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
	this->animaVec[crop_PicData[cropNum].startCropVecNum + crop_PicData[cropNum].maxGrowth-1].DrawAnima(5, 95,45,135);
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
					if ((*playerScore) >= crop_PicData[(*data).cropNum].cost) {
						this->map[(*data).x][(*data).y] = 1;
						CROP crop((*data).x, (*data).y, (*data).cropNum, crop_PicData[(*data).cropNum].maxGrowth, crop_PicData[(*data).cropNum].score, crop_PicData[(*data).cropNum].cropPicDataVec[(*data).cropNum].cropPicHandle);
						int count = 0;
						for (int j = 0; j < crop_PicData[(*data).cropNum].maxGrowth; j++) {
							crop.anima.push_back(this->animaVec[crop_PicData[(*data).cropNum].startCropVecNum + j]);
						}
						this->cropVec.push_back(crop);
						//this->cost = crop_PicData[(*data).cropNum].cost;
						*playerScore -= crop_PicData[(*data).cropNum].cost;
						this->sound.LoadSound("Sound/シャベルで穴掘り.mp3");
						this->sound.PlayBGMSound();
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
							this->cropVec[i].time = this->cropVec[i].time + 10;
							this->sound.LoadSound("Sound/水ちょろちょろ.mp3");
							this->sound.PlayBGMSound();
						}
					}
				}
				break;
				//ツールが"ハサミ"のとき
			case 2:
				switch (this->map[(*data).x][(*data).y]) {
					//農地に作物がないとき
				case 0:
					break;
				case 1:
					//(*data).returnScore = ReturnScore((*data).x, (*data).y);
					*playerScore += ReturnScore((*data).x, (*data).y);
					this->DeleteCROP((*data).x, (*data).y);
					this->sound.LoadSound("Sound/ラップをちぎる.mp3");
					this->sound.PlayBGMSound();
					break;
				}
			}
			break;
		//リターン(エンター)キーが押されたとき
		/*case Action_RETURN:
			(*data).score = ReturnScore((*data).x, (*data).y);
			this->DeleteCROP((*data).x, (*data).y);
			break;
		*/
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
		for (int j = 0; j < crop_PicData[i].cropPicDataVec.size(); j++) {
			crop_PicData[i].cropPicDataVec[j].cropPicHandle = LoadGraph(crop_PicData[i].cropPicDataVec[j].cropPicName);
			ANIMATION_DATA animaData = { crop_PicData[i].cropPicDataVec[j].startFrame, crop_PicData[i].cropPicDataVec[j].endFrame,
				crop_PicData[i].cropPicDataVec[j].cropPicHandle };
			this->animaVec[crop_PicData[i].cropPicDataVec[j].cropGrow + crop_PicData[i].startCropVecNum].anima.push_back(animaData);
		}
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