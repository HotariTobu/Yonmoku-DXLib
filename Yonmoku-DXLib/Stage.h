#pragma once

#include "Main.h"

#include "Stand.h"
#include "Stone.h"

class Stage {
public:
	void init(bool turn);
	void update();
	void draw();
	void dispose();

	void mouseClicked(int button);
	void mouseMoved();
	void mouseDragged(int x, int y, int button);
	void mouseWheel(int value);
	
	void resetStones();
	static void resetStones(int stones[4][16]);

	int CheckLine();
	static int CheckLine(int stones[4][16]);

	void drop(int index, int type);

	bool turn;

private:
	void rotate(float *x, float *y, const int ang);

	Stand stand;
	Stone stone;

	float cameraX, cameraY, cameraZ;
	int distance;
	int angleH, angleV;

	int stones[4][16];

};