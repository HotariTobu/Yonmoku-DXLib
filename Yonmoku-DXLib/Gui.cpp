#include"Gui.h"

//----------------------------------------------------------------------------------------------
void Gui::init() {
	image = LoadGraph("impo/Gui.png");

	int ImageWidth, ImageHeight;
	GetGraphSize(image, &ImageWidth, &ImageHeight);

	x = (640 - ImageWidth) / 2;
	y = (480 - ImageHeight) / 2;

}

//----------------------------------------------------------------------------------------------
void Gui::draw() {
	DrawGraph(x, y, image, true);
}

//----------------------------------------------------------------------------------------------
void Gui::dispose() {
	DeleteGraph(image);
}