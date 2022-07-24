#pragma once

#include "Main.h"

class Input {
public :
	void init(int inputMax, int y = 160);
	void update();
	void draw();
	void dispose();

	void mouseClicked(int button);
	void mouseMoved(int x, int y);
	
	bool hit;

	int result;
	char *text;

private :
	int box;
	int x, y;
	int width, height;

};