#pragma once

#include "Main.h"

class No {
public :
	void init();
	void update();
	void draw();
	void dispose();

	void mouseMoved(int x, int y);

	bool hit;

private :
	int image;
	int ImageX1, ImageY1, ImageX2, ImageY2;
	int ImageWidth, ImageHeight;
	int ImageAddition;

	int scaleFrame, scaleDelimit;

	void GetMiddle();

};