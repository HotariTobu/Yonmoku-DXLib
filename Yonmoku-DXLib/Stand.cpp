#include "Stand.h"

//----------------------------------------------------------------------------------------------
void Stand::init() {
	model = MV1LoadModel("impo/Stand.mqo");
	MV1SetupCollInfo(model);

	mesh = MV1GetMeshNum(model);

	MV1SetPosition(model, VGet(0, -20, 0));

}

//----------------------------------------------------------------------------------------------
void Stand::update() {
	if (index > 0) {
		for (int i = 1; i < mesh; i++) {
			if (index == MV1GetMeshMaterial(model, i)) {
				MV1SetMeshOpacityRate(model, i, 1.0f);

			}
			else {
				MV1SetMeshOpacityRate(model, i, 0.4f);

			}

		}

	}
	else {
		for (int i = 1; i < mesh; i++) {
			MV1SetMeshOpacityRate(model, i, 1.0f);

		}

	}

}

//----------------------------------------------------------------------------------------------
void Stand::draw() {
	MV1DrawModel(model);

}

//----------------------------------------------------------------------------------------------
void Stand::dispose() {
	MV1DeleteModel(model);

}

void Stand::mouseMoved() {
	MV1RefreshCollInfo(model, -1);

	hp = MV1CollCheck_Line(model, -1, sp, ep);

	hit = hp.HitFlag;
	if (hit) {
		index = hp.MaterialIndex;
	}
	else {
		index = 0;
	}

}