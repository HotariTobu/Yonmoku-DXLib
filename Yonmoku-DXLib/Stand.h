#pragma once

#include "Main.h"

class Stand {
public:
	void init();
	void update();
	void draw();
	void dispose();

	void mouseMoved();

	bool hit;
	int index;

private:
	int model;
	int mesh;

};