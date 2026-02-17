#include"Input.h"
#include<random>

class InputNPC : public Input {
public:
	void Update(int toolNum) override;
	void Agent();
public:
	std::random_device rd;
};