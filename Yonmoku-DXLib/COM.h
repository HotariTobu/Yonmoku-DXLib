#pragma once

#include "Main.h"

#include <fstream>
#include <filesystem>

#include "Stage.h"

using namespace experimental::filesystem;

struct pattern {
	unsigned int pattern01[128]{};
	unsigned int pattern02[8192]{};
	unsigned int pattern03[508160]{};

};

class COM {
public :
	COM();
	~COM();

	void push(int index);
	int pull();

	int stones[4][16];

private:
	pattern patterns[16];

	void count(int tree, unsigned int *pattern, int *id, int j = 0, int limit = 64);
	void count(int tree, unsigned int *pattern, int *id, unsigned int *result, int j = 0, int limit = 64);

};