#include"EXIT.h"

//----------------------------------------------------------------------------------------------
void EXIT::init() {
	hit = false;
	model = MV1LoadModel("impo/EXIT.mqo");
	MV1SetupCollInfo(model);

	MV1SetPosition(model, VGet(0, 0, -10));

}

//----------------------------------------------------------------------------------------------
void EXIT::draw() {
	MV1DrawModel(model);

}

//----------------------------------------------------------------------------------------------
void EXIT::dispose() {
	MV1DeleteModel(model);

}

//----------------------------------------------------------------------------------------------
void EXIT::mouseClicked(int button) {
	if (hit && button == MOUSE_INPUT_LEFT) {
		Pause();

	}

}

//----------------------------------------------------------------------------------------------
void EXIT::mouseMoved() {
	MV1RefreshCollInfo(model, -1);

	hp = MV1CollCheck_Line(model, -1, sp, ep);

	hit = hp.HitFlag;
	if (hit) {
		MV1SetEmiColorScale(model, GetColorF(1.0f, 5.0f, 1.0f, 1.0f));

	}
	else {
		MV1SetEmiColorScale(model, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

	}

}