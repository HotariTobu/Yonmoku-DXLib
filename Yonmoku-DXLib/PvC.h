#pragma once

#include "Main.h"

class PvC {
public:
	void init();
	void update();
	void draw();
	void dispose();

	void mouseClicked(int button);
	void mouseMoved();

private:
	int model;
	bool hit;

	float rotate;
	int rotateFrame, rotateDelimit;

};