#include"Input.h"
#include"Crop.h"
#include<random>
#include"Tool.h"

#define WIDTH 40
#define HEIGHT 40
#define MAP_SELL_LENGTH 15

class InputNPC_Learning : public Input {
public:
	InputNPC_Learning();
	//void Update(int toolNum) override;
	void Update(int time, int toolNum, int cropNum, int score, int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData);
	void Agent(int time, int toolNum, int cropNum, int score, int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData);
	bool SearchGrownCrop(std::vector<CROP>* cropVec, int x, int y); //ì•¨ƒŠƒXƒg‚©‚çˆø”‚ÌˆÊ’u‚Ìì•¨‚ªûŠn‰Â”\‚©ŒŸõ
	int getGrownCropNum(std::vector<CROP>* cropVec, int x, int y); //ûŠn—\’èì•¨‚Ì’†‚Å‘ÎÛ‚Ìì•¨‚ğŒŸõ
	void InitCropGrownVec(); //ûŠn—\’èì•¨‚Ì‰Šú‰»
	COORDINATE selectAction(int map[][HEIGHT], std::vector<CROP>* cropVec,int x, int y);
	float getReward(int map[][HEIGHT], std::vector<CROP>* cropVec, int x, int y);
	std::vector<float> getRewardList(int map[][HEIGHT], std::vector<CROP>* cropVec, int x, int y);
	float getMaxNextQ(int map[][HEIGHT], std::vector<CROP>* cropVec, int x, int y);
public:
	std::random_device rd;
	std::vector<CROP> cropGrownVec; //ûŠn—\’èì•¨
	std::vector<CROP> myCropVec;
	std::vector<float> qVec;
	int action;
	COORDINATE returnXY;
};