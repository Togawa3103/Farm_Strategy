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

typedef struct {
	int x;
	int y;
}COORDINATE;

class InputNPC : public Input {
public:
	//void Update(int toolNum) override;
	void Update(int toolNum, int cropNum, int score,int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData);
	void Agent(int toolNum, int cropNum, int score, int x, int y, int map[][HEIGHT], std::vector<CROP>* cropVec, std::vector<CROP_PIC>* cropData, std::vector<TOOL_PIC>* toolData);
	bool SearchGrownCrop(std::vector<CROP>* cropVec, int x, int y); //作物リストから引数の位置の作物が収穫可能か検索
	int getGrownCropNum(std::vector<CROP>* cropVec, int x, int y); //
	COORDINATE getNeighborhoodFreeSpace(int map[][HEIGHT], int x, int y); //近隣8マスの空いている土地で近いものを検索
public:
	std::random_device rd;
	std::vector<CROP> cropGrownVec; //収穫予定作物
	std::vector<CROP> myCropVec;
};