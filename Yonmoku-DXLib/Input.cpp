#include "Input.h"

//----------------------------------------------------------------------------------------------
void Input::init(int inputMax,int y) {
	result = 0;
	text = new char[inputMax];

	box = MakeKeyInput(inputMax, false, false, false, false, false);
	SetActiveKeyInput(box);

	x = 320;
	this->y = y;

}

//----------------------------------------------------------------------------------------------
void Input::update() {
	if (result == 0) {
		result = CheckKeyInput(box);

		GetKeyInputString(text, box);

		GetDrawStringSize(&width, &height, NULL, text, GetStringLength(text));
		x = (640 - width) / 2;
	}

}

//----------------------------------------------------------------------------------------------
void Input::draw() {
	if (result == 0) {
		DrawKeyInputString(x, y, box);
	}
	else if (result==1) {
		DrawString(x, y, text, GetColor(0, 0, 255));
	}

}

//----------------------------------------------------------------------------------------------
void Input::dispose() {
	DeleteKeyInput(box);

}

//----------------------------------------------------------------------------------------------
void Input::mouseClicked(int button) {
	if (hit && button == MOUSE_INPUT_LEFT && result != 0) {
		SetActiveKeyInput(box);

		result = 0;
	}

}

//----------------------------------------------------------------------------------------------
void Input::mouseMoved(int x, int y) {
	hit = (this->x < x && this->x + width > x) && (this->y < y && this->y + height > y);

}