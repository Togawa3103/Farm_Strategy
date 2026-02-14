#include"Input.h"

Input::Input() {
	this->keyState;
	this->frame = 0;
}

Input::~Input() {}

void Input::Update(int toolNum) {
	GetHitKeyStateAll(this->keyState); //キー入力取得
	if (this->frame > 0) {
		this->keyState[KEY_INPUT_E] = 0;
		this->keyState[KEY_INPUT_Q] = 0;
		this->keyState[KEY_INPUT_Z] = 0;

		this->keyState[KEY_INPUT_SPACE] = 0;
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
	else if (toolNum == 1&& this->keyState[KEY_INPUT_SPACE]) {
		this->frame++;
	}
}

void Input::InitInput() {
	if(this->frame>50)this->frame = 0;
}

void Input::Update_StartMenu() {
	GetHitKeyStateAll(this->keyState); //キー入力取得
	if (this->frame > 0) {
		this->keyState[KEY_INPUT_W] = 0;
		this->keyState[KEY_INPUT_S] = 0;
		this->keyState[KEY_INPUT_RETURN] = 0;

		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_W]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_S]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_RETURN]) {
		this->frame++;
	}
}

void Input::Update_ResultMenu() {
	GetHitKeyStateAll(this->keyState); //キー入力取得
	if (this->frame > 0) {
		this->keyState[KEY_INPUT_W] = 0;
		this->keyState[KEY_INPUT_S] = 0;
		this->keyState[KEY_INPUT_RETURN] = 0;
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_W]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_S]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_RETURN]) {
		this->frame++;
	}
}