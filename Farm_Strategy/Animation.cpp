#include"Animation.h"

Animation::Animation() {
	this->anima;
	this->frame = 0;
}

Animation::~Animation() {}

void Animation::Update() {
	this->frame++;
	if (this->anima[this->anima.size() - 1].endFrame == frame) {
		this->frame = 0;
	}
}

void Animation::DrawAnima(int startX, int startY, int endX, int endY) {
	//アニメーションを行うとき
	if (this->anima[0].endFrame - this->anima[0].startFrame > 0) {
		for (int i = 0; i < this->anima.size(); i++) {
			if (this->anima[i].startFrame <= this->frame&& this->anima[i].endFrame > this->frame) {
				DrawExtendGraph(startX, startY, endX, endY,
					this->anima[i].graphHandle, TRUE);
			}
		}
	}
	//アニメーションを行わないとき(画像描写のみ)
	else {
		DrawExtendGraph(startX, startY, endX, endY,
			this->anima[0].graphHandle, TRUE);
	}
}