#include"Input_NPC.h"

void InputNPC::Update(int toolNum) {
	memset(this->keyState, 0, sizeof(char) * 256);
	this->Agent();
	if (this->frame > 0) {
		this->keyState[KEY_INPUT_E] = 0;
		this->keyState[KEY_INPUT_Q] = 0;
		this->keyState[KEY_INPUT_Z] = 0;

		//this->keyState[KEY_INPUT_SPACE] = 0;
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_E]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_Q]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_Z]) {
		this->frame++;
	}
	/*else if (toolNum == 1 && this->keyState[KEY_INPUT_SPACE]) {
		this->frame++;
	}*/
}

void InputNPC::Agent() {
	int random_number = rd()%120;
	if (random_number>=0&&random_number<15) {
		this->keyState[KEY_INPUT_E] = 1;
	}
	if (random_number >= 15 && random_number < 30) {
		this->keyState[KEY_INPUT_Q] = 1;
	}
	if (random_number >= 30 && random_number < 45) {
		this->keyState[KEY_INPUT_Z] = 1;
	}
	if (random_number >= 45 && random_number < 60) {
		this->keyState[KEY_INPUT_W] = 1;
	}
	if (random_number >= 60 && random_number < 75) {
		this->keyState[KEY_INPUT_A] = 1;
	}
	if (random_number >= 75 && random_number < 90) {
		this->keyState[KEY_INPUT_S] = 1;
	}
	if (random_number >= 90 && random_number < 105) {
		this->keyState[KEY_INPUT_D] = 1;
	}
	if (random_number >= 105 && random_number < 120) {
		this->keyState[KEY_INPUT_SPACE] = 1;
	}
}