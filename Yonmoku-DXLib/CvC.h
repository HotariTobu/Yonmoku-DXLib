#pragma once

#include "Main.h"

#include "COM.h"
#include "Stage.h"

class CvC {
public:
	void init();
	void update();
	void draw();
	void dispose();

	void mouseClicked(int button);
	void mouseMoved();

private:
	void dropDummy(int index, int type, int stones[4][16]);

	int model;
	bool hit;

	float rotate;
	int rotateFrame, rotateDelimit;

};