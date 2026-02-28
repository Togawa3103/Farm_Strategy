#include"Input.h"
#include"Crop.h"
#include<random>
#include"Tool.h"

#define WIDTH 40
#define HEIGHT 40
#define MAP_SELL_LENGTH 15
enum {
	Tool_InputNPC_Hoe,
	Tool_InputNPC_WateringCan,
	Tool_InputNPC_Scissors,
	Tool_InputNPC_MAX,
};
typedef struct {
	int x;
	int y;
}GROWNCROP;

class InputNPC : public Input {
public:
	//void Update(int toolNum) override;
	void Update(int toolNum, int cropNum, int score,int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData);
	void Agent(int toolNum, int cropNum, int score, int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData);
	bool SearchGrownCrop(std::vector<CROP>* cropVec, int x, int y);
	int getGrownCropNum(std::vector<CROP>* cropVec, int x, int y);
public:
	std::random_device rd;
	std::vector<CROP> cropGrownVec;
	std::vector<CROP> myCropVec;
};