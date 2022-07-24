#ifndef MAIN_H
#define MAIN_H

#pragma once

#include <DxLib.h>
#include <math.h>
#include <string>

#include "Gui.h"

using namespace std;

class Main {
public :
	void init();
	void update();
	void draw();
	void dispose();

	void keyInput(int key);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mouseWheel(int value);

	void push(int index);
	void pull();

};

extern Main GetMain();

extern bool quit;
extern int state;
extern VECTOR sp, ep;
extern MV1_COLL_RESULT_POLY hp;

extern void ChangeState(int changedState);

extern int GetInterval(int millis);
extern float GetRedian(float si);

extern void Pause();

#endif