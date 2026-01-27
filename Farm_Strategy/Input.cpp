#include"Input.h"

Input::Input() {
	this->keyState;
}

Input::~Input() {}

void Input::Update() {
	GetHitKeyStateAll(this->keyState); //ƒL[“ü—Íæ“¾
}

