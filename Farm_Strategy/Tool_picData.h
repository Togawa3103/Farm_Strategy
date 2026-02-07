#pragma once
#include"Tool.h"
enum {
	Tool_Hoe,
	Tool_WateringCan,
	Tool_Scissors,
	Tool_MAX,
};

std::vector<TOOL_PIC> tool_PicData = {
	{0,0,2,{{"Tool_Hoe1.bmp",-1, 0,100},{"Tool_Hoe2.bmp",-1,100,200}},{{100,0,0,0,0},{200,-1,0,1,0},{0,-1,-1,1,1}}},
	{1,0,2,{{"Tool_WateringCan1.bmp",-1, 0,100},{"Tool_WateringCan2.bmp",-1,100,200}},{{150,0,0,0,0},{250,-1,0,1,0},{0,-1,-1,1,1}}},
	{2,0,2,{{"Tool_Scissors1.bmp",-1, 0,100},{"Tool_Scissors2.bmp",-1,100,200}},{{200,0,0,0,0},{300,-1,0,1,0},{0,-1,-1,1,1}}},
};