#include"CvC.h"

//----------------------------------------------------------------------------------------------
void CvC::init() {
	hit = false;
	model = MV1LoadModel("impo/CvC.mqo");
	MV1SetupCollInfo(model);

	MV1SetPosition(model, VGet(-10, 0, 0));

	rotate = 0.0f;
	rotateFrame = 0;
	rotateDelimit = GetInterval(50);

}

//----------------------------------------------------------------------------------------------
void CvC::update() {
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
void CvC::draw() {
	MV1DrawModel(model);

}

//----------------------------------------------------------------------------------------------
void CvC::dispose() {
	MV1DeleteModel(model);

}

//----------------------------------------------------------------------------------------------
void CvC::mouseClicked(int button) {
	if (hit && button == MOUSE_INPUT_LEFT) {
		COM *com1 = new COM();
		COM *com2 = new COM(*com1);

		{
			int GHandle = MakeGraph(640, 480);
			GetMain().draw();
			GetDrawScreenGraph(0, 0, 640, 480, GHandle);

			Gui gui;
			Message mess;

			gui.init();
			mess.init("ESC‚ÅI—¹", 140, GetColor(10, 10, 10));

			DrawGraph(0, 0, GHandle, false);
			gui.draw();
			mess.draw();
			
			ScreenFlip();

			int stones[4][16];

			Stage::resetStones(stones);

			while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
				int index = com1->pull();
				com2->push(index);

				dropDummy(index, 1, stones);
				if (Stage::CheckLine(stones) != 0) {
					Stage::resetStones(stones);

				}

				index = com2->pull();
				com1->push(index);

				dropDummy(index, 2, stones);
				if (Stage::CheckLine(stones) != 0) {
					Stage::resetStones(stones);

				}

			}

			DeleteGraph(GHandle);
			gui.dispose();

			while (CheckHitKey(KEY_INPUT_ESCAPE));

		}

		delete com1;
		delete com2;

	}

}

//----------------------------------------------------------------------------------------------
void CvC::mouseMoved() {
	MV1RefreshCollInfo(model, -1);

	hp = MV1CollCheck_Line(model, -1, sp, ep);

	hit = hp.HitFlag;
	if (hit) {
		MV1SetEmiColorScale(model, GetColorF(1.0f, 1.0f, 0.0f, 1.0f));

	}
	else {
		MV1SetEmiColorScale(model, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

	}

}

void CvC::dropDummy(int index, int type, int stones[4][16]) {
	int depth = 0;
	for (; depth <= 4; depth++) {
		if (stones[depth][index] == 0) {
			break;

		}

	}

	if (depth == 4) {
		return;

	}

	stones[depth][index] = type;

}