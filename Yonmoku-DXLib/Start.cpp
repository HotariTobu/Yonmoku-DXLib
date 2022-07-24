#include"Start.h"

//----------------------------------------------------------------------------------------------
void Start::init() {
	HRotate = 0.0f;

	SetCameraPositionAndAngle(VGet(0, 0, 0), 0, 0, 0);

	pvp.init();
	pvc.init();
	cvc.init();
	Exit.init();

}

//----------------------------------------------------------------------------------------------
void Start::update() {
	pvp.update();
	pvc.update();
	cvc.update();

}

//----------------------------------------------------------------------------------------------
void Start::draw() {
	pvp.draw();
	pvc.draw();
	cvc.draw();
	Exit.draw();

}

//----------------------------------------------------------------------------------------------
void Start::dispose() {
	pvp.dispose();
	pvc.dispose();
	cvc.dispose();
	Exit.dispose();

}

//----------------------------------------------------------------------------------------------
void Start::mouseClicked(int button) {
	pvp.mouseClicked(button);
	pvc.mouseClicked(button);
	cvc.mouseClicked(button);
	Exit.mouseClicked(button);

}

//----------------------------------------------------------------------------------------------
void Start::mouseMoved() {
	pvp.mouseMoved();
	pvc.mouseMoved();
	cvc.mouseMoved();
	Exit.mouseMoved();

}

void Start::mouseDragged(int x, int button) {
	if (button == MOUSE_INPUT_RIGHT) {
		HRotate += x / 4;
	}

	SetCameraPositionAndAngle(VGet(0, 0, 0), 0, (DX_PI * HRotate / 180), 0);

}