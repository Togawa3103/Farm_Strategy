#pragma once
#include<vector>

typedef struct {
	int cropGrow;
	const char* cropPicName;
	int cropPicHandle;
}CROP_DATA;
typedef struct {
	int cropNum;
	std::vector<CROP_DATA> cropPicDataVec;
}CROP_PIC;
