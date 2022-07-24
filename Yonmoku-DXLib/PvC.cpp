#include"PvC.h"

//----------------------------------------------------------------------------------------------
void PvC::init() {
	hit = false;
	model = MV1LoadModel("impo/PvC.mqo");
	MV1SetupCollInfo(model);

	MV1SetPosition(model, VGet(10, 0, 0));

	rotate = 0.0f;
	rotateFrame = 0;
	rotateDelimit = GetInterval(50);

}

//----------------------------------------------------------------------------------------------
void PvC::update() {
	rotateFrame++;

	if (rotateFrame == rotateDelimit) {
		if (hit) {
			rotate -= 2.5f;
		}
		else {
			rotate -= 0.5f;
		}

		rotateFrame = 0;
	}

	MV1SetRotationXYZ(model, VGet(0.0f, GetRedian(rotate), 0.0f));

}

//----------------------------------------------------------------------------------------------
void PvC::draw() {
	MV1DrawModel(model);

}

//----------------------------------------------------------------------------------------------
void PvC::dispose() {
	MV1DeleteModel(model);

}

//----------------------------------------------------------------------------------------------
void PvC::mouseClicked(int button) {
	if (hit && button == MOUSE_INPUT_LEFT) {
		ChangeState(2);

	}

}

//----------------------------------------------------------------------------------------------
void PvC::mouseMoved() {
	MV1RefreshCollInfo(model, -1);

	hp = MV1CollCheck_Line(model, -1, sp, ep);

	hit = hp.HitFlag;
	if (hit) {
		MV1SetEmiColorScale(model, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));

	}
	else {
		MV1SetEmiColorScale(model, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

	}

}