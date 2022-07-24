#pragma once

#include "Main.h"

class EXIT {
public :
	void init();
	void draw();
	void dispose();

	void mouseClicked(int button);
	void mouseMoved();

private :
	int model;
	bool hit;

};