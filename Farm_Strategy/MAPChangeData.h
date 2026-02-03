#pragma once

enum {
	Action_SPACE,
	Action_RETURN,
	Actoin_MAX
};


struct RETURN_DATA
{
	int x;
	int y;
	int actionFlag;
	int cropNum;
	int toolNum;
	int score;
} ;