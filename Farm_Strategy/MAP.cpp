#include"MAP.h"

MAP::MAP() {
	this->color_white = GetColor(255, 255, 255);
	this->color_black = GetColor(0, 0, 0);
	this->color_red = GetColor(255, 0, 0);

	//map‚Ì‰Šú‰»
	for (int i = 0; i < WIDTH;i++) {
		for (int j = 0; j < HEIGHT;j++) {
			this->map[i][j] = 0;
		}
	}
}

MAP::~MAP() {}

void MAP::Update(RETURN_DATA data) {
	this->GetMAPChangeData(data);
}

void MAP::DrawMAP() {
	DrawBox(MAPBG_START_WIDTH, MAPBG_START_HEIGHT, MAPBG_END_WIDTH, MAPBG_END_HEIGHT, this->color_white, TRUE);
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			DrawBox(MAPW_START_WIDTH + MAP_SELL_LENGTH * i, MAPW_START_HEIGHT + MAP_SELL_LENGTH * j,
				MAPW_END_WIDTH + MAP_SELL_LENGTH * i, MAPW_END_HEIGHT + MAP_SELL_LENGTH * j, this->color_white, TRUE);
			switch(this->map[i][j]){
			case 1:
				DrawBox(MAPB_START_WIDTH + MAP_SELL_LENGTH * i, MAPB_START_HEIGHT + MAP_SELL_LENGTH * j,
				MAPB_END_WIDTH + MAP_SELL_LENGTH * i, MAPB_END_HEIGHT + MAP_SELL_LENGTH * j, this->color_red,TRUE);
				break;
			case 0:
				DrawBox(MAPB_START_WIDTH + MAP_SELL_LENGTH * i, MAPB_START_HEIGHT + MAP_SELL_LENGTH * j,
					MAPB_END_WIDTH + MAP_SELL_LENGTH * i, MAPB_END_HEIGHT + MAP_SELL_LENGTH * j, this->color_black, TRUE);
				break;
			}
		}
	}
}

void MAP::GetMAPChangeData(RETURN_DATA data) {
	if(data.x>=0&&data.y>=0)
	this->map[data.x][data.y] = 1;
}