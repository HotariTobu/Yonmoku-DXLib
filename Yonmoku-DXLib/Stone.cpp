#include "Stone.h"

//----------------------------------------------------------------------------------------------
void Stone::init() {
	model = MV1LoadModel("impo/Stone.mqo");

}

//----------------------------------------------------------------------------------------------
void Stone::update(const float (&vector)[3], int type) {
	MV1SetPosition(model, VGet(vector[0], vector[1], vector[2]));

	DxLib::COLOR_F Scale;

	switch (type) {
	case 1:
		Scale = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);

		break;
	case 2:
		Scale = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);

		break;
	case 3:
		Scale = GetColorF(1.0f, 1.0f, 0.0f, 1.0f);

		break;
	}

	MV1SetDifColorScale(model, Scale);
	MV1SetSpcColorScale(model, Scale);
	MV1SetEmiColorScale(model, Scale);
	MV1SetAmbColorScale(model, Scale);

}

//----------------------------------------------------------------------------------------------
void Stone::draw() {
	MV1DrawModel(model);

}

//----------------------------------------------------------------------------------------------
void Stone::dispose() {
	MV1DeleteModel(model);

}

//----------------------------------------------------------------------------------------------
void Stone::SetOpacity(float rate) {
	MV1SetOpacityRate(model, rate);

}