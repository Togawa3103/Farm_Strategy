#include"MAP.h"
#include"Crop_PicData.h"

MAP::MAP() {
	this->color_white = GetColor(255, 255, 255);
	this->color_black = GetColor(0, 0, 0);
	this->color_red = GetColor(255, 0, 0);

	//mapÇÃèâä˙âª
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
}

MAP::~MAP() {}

void MAP::Update(RETURN_DATA data) {
	this->GetMAPChangeData(data);
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

void MAP::GetMAPChangeData(RETURN_DATA data) {
	if (data.x >= 0 && data.y >= 0) {
		switch (data.actionFlag) {
		case Action_SPACE:
			if(this->map[data.x][data.y]==0){			
				this->map[data.x][data.y] = 1;
				CROP crop(data.x, data.y, 0, crop_PicData[0].cropPicDataVec[0].cropPicHandle);
				int count=0;
				for (int i = 0;i < crop_PicData.size(); i++) {
					count=count+ crop_PicData[i].cropNum * crop_PicData[i].maxGrowth;
					if (crop.cropNum== crop_PicData[i].cropNum) {
						for (int j = count; j < crop_PicData[i].maxGrowth;j++) {
							crop.anima.push_back(this->animaVec[j]);
						}
					}
				}
				this->cropVec.push_back(crop);
			}
			break;
		case Action_RETURN:
			this->DeleteCROP(data.x, data.y);
			break;
		}
	}
}

void MAP::UpdateCROP() {
	for (int i = 0; i < this->cropVec.size(); i++) {
		this->cropVec[i].Update();
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
			this->animaVec[crop_PicData[i].cropPicDataVec[j].cropGrow].anima.push_back(animaData);
		}
	}
}