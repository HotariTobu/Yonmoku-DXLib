#pragma once

#include "Main.h"

#include "PvP.h"
#include "PvC.h"
#include "CvC.h"
#include "EXIT.h"

class Start {
public:
	void init();
	void update();
	void draw();
	void dispose();

	void mouseClicked(int button);
	void mouseMoved();
	void mouseDragged(int x, int button);

	PvP pvp;
	PvC pvc;
	CvC cvc;
	EXIT Exit;

private:
	float HRotate;

};