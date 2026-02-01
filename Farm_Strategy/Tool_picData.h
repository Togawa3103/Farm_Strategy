#pragma once
#include"Tool.h"
enum {
	Tool_Hoe,
	Tool_WateringCan,
	Tool_MAX,
};

std::vector<TOOL_PIC> tool_PicData = {
	{0,{{"Tool_Hoe1.bmp",-1, 0,100},{"Tool_Hoe2.bmp",-1,100,200}}},
	{1,{{"Tool_WateringCan1.bmp",-1, 0,100},{"Tool_WateringCan2.bmp",-1,100,200}}}
};