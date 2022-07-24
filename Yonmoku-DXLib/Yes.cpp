#include"Yes.h"

//----------------------------------------------------------------------------------------------
void Yes::init() {
	hit = false;
	image = LoadGraph("impo/Yes.png");

	GetGraphSize(image, &ImageWidth, &ImageHeight);
	ImageAddition = 0;

	GetMiddle();

	scaleFrame = 0;
	scaleDelimit = GetInterval(50);
}

//----------------------------------------------------------------------------------------------
void Yes::update() {
	scaleFrame++;

	if (scaleFrame == scaleDelimit) {
		if (hit) {
			if (ImageAddition != 20) {
				ImageAddition += 2;

				GetMiddle();
			}
		}
		else {
			if (ImageAddition != 0) {
				ImageAddition -= 2;

				GetMiddle();
			}
		}

		scaleFrame = 0;
	}
}

//----------------------------------------------------------------------------------------------
void Yes::draw() {
	DrawExtendGraph(ImageX1, ImageY1, ImageX2, ImageY2, image, true);
}

//----------------------------------------------------------------------------------------------
void Yes::dispose() {
	DeleteGraph(image);
}

//----------------------------------------------------------------------------------------------
void Yes::mouseMoved(int x, int y) {
	hit = (ImageX1 < x && ImageX2 > x) && (ImageY1 < y && ImageY2 > y);
}

//----------------------------------------------------------------------------------------------
void Yes::GetMiddle() {
	int width = ImageWidth + ImageAddition;
	int height = ImageHeight + ImageAddition;

	ImageX1 = (640 - (width + 100 + ImageWidth)) / 2;
	ImageX2 = ImageX1 + width;
	ImageY1 = 320 - ImageAddition / 2;
	ImageY2 = ImageY1 + height;
}