#pragma once

enum {
	Action_SPACE,
	Action_RETURN,
	Actoin_MAX
};


typedef struct RETURN_DATA
{
	int playerNum;
	int x;
	int y;
	int actionFlag;
	int cropNum;
	int toolNum;
	int returnScore;
} ;
