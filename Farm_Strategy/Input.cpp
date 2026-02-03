#include"Input.h"

Input::Input() {
	this->keyState;
	this->frame = 0;
}

Input::~Input() {}

void Input::Update() {
	GetHitKeyStateAll(this->keyState); //ƒL[“ü—ÍŽæ“¾
	if (this->frame > 0) {
		this->keyState[KEY_INPUT_E] = 0;
		this->keyState[KEY_INPUT_Q] = 0;
		//this->keyState[KEY_INPUT_SPACE] = 0;
		this->frame++;
	}else if (this->keyState[KEY_INPUT_E]) {
		this->frame++;
	}
	else if (this->keyState[KEY_INPUT_Q]) {
		this->frame++;
	}
	//else if (this->keyState[KEY_INPUT_SPACE]) {
	//	this->frame++;
	//}
}

void Input::InitInput() {
	if(this->frame>200)this->frame = 0;
}

