#pragma once

#include "Main.h"

#include "Message.h"
#include "Input.h"
#include "Cancel.h"
#include "Yes.h"
#include "No.h"

class Gui {
public:
	void init();
	void draw();
	void dispose();

private:
	int image;
	int x, y;

};