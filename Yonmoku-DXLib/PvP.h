#pragma once

#include "Main.h"

class PvP {
public:
	void init();
	void update();
	void draw();
	void dispose();

	void mouseClicked(int button);
	void mouseMoved();

	bool client;
	int partner;

private:
	int model;
	bool hit;

	float rotate;
	int rotateFrame, rotateDelimit;

};