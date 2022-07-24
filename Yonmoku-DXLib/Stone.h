#pragma once

#include "Main.h"

class Stone {
public:
	void init();
	void update(const float(&vector)[3], int type);
	void draw();
	void dispose();

	void SetOpacity(float rate);

private:
	int model;

};