#include "COM.h"

//----------------------------------------------------------------------------------------------
COM::COM() {
	if (exists(path("com"))) {
		string dir;
		for (int i = 0; i < 16; i++) {
			dir = ("com/" + to_string(i));
			if (exists(path(dir))) {
				string file;

				file = dir + "/01.txt";
				if (exists(path(file))) {
					ifstream is(file, ios::binary);

					for (int j = 0; j < ARRAYSIZE(patterns[i].pattern01); j++) {
						unsigned int t = 0;

						is.read((char *)&t, sizeof(unsigned int));

						if (t < 0) {
							patterns[i].pattern01[j] = 0;

						}
						else {
							patterns[i].pattern01[j] = t;

						}

					}

					is.close();

				}

				file = dir + "/02.txt";
				if (exists(path(file))) {
					ifstream is(file, ios::binary);

					for (int j = 0; j < ARRAYSIZE(patterns[i].pattern02); j++) {
						unsigned int t = 0;

						is.read((char *)&t, sizeof(unsigned int));

						if (t < 0) {
							patterns[i].pattern02[j] = 0;

						}
						else {
							patterns[i].pattern02[j] = t;

						}

					}

					is.close();

				}

				file = dir + "/03.txt";
				if (exists(path(file))) {
					ifstream is(file, ios::binary);

					for (int j = 0; j < ARRAYSIZE(patterns[i].pattern03); j++) {
						unsigned int t = 0;

						is.read((char *)&t, sizeof(unsigned int));

						if (t < 0) {
							patterns[i].pattern03[j] = 0;

						}
						else {
							patterns[i].pattern03[j] = t;

						}

					}

					is.close();

				}

			}

		}

	}

	Stage::resetStones(stones);

}

/*string buf;
getline(is, buf);
for (int j = 0; j < ARRAYSIZE(patterns[i].pattern01); j++) {
unsigned int t = 0;

t = t | ((unsigned int)buf.at(j * 4));
t = t | (((unsigned int)buf.at(j * 4 + 1)) << 8);
t = t | (((unsigned int)buf.at(j * 4 + 2)) << 16);
t = t | (((unsigned int)buf.at(j * 4 + 3)) << 24);

if (t < 0) {
patterns[i].pattern01[j] = 0;

}
else {
patterns[i].pattern01[j] = t;

}

}*/

//----------------------------------------------------------------------------------------------
COM::~COM() {
	if (!exists(path("com"))) {
		create_directory(path("com"));

	}

	string dir;
	for (int i = 0; i < 16; i++) {
		dir = ("com/" + to_string(i));
		if (!exists(path(dir))) {
			create_directory(path(dir));

		}

		string file;

		file = dir + "/01.txt";
		{
			ofstream os(file, ios::binary);

			for (int j = 0; j < ARRAYSIZE(patterns[i].pattern01); j++) {
				os.write((char *)&(patterns[i].pattern01[j]), sizeof(unsigned int));

			}

			os.close();

		}

		file = dir + "/02.txt";
		{
			ofstream os(file, ios::binary);

			for (int j = 0; j < ARRAYSIZE(patterns[i].pattern02); j++) {
				os.write((char *)&(patterns[i].pattern02[j]), sizeof(unsigned int));

			}

			os.close();

		}

		file = dir + "/03.txt";
		{
			ofstream os(file, ios::binary);

			for (int j = 0; j < ARRAYSIZE(patterns[i].pattern03); j++) {
				os.write((char *)&(patterns[i].pattern03[j]), sizeof(unsigned int));

			}

			os.close();

		}

	}

}

/*string buf;
for (int j = 0; j < ARRAYSIZE(patterns[i].pattern01); j++) {
buf.push_back(((patterns[i].pattern01[j] << 24) >> 24));
buf.push_back(((patterns[i].pattern01[j] << 16) >> 24));
buf.push_back(((patterns[i].pattern01[j] << 8) >> 24));
buf.push_back((patterns[i].pattern01[j] >> 24));

}
os << buf;*/

//----------------------------------------------------------------------------------------------
void COM::push(int index) {
	int depth = 0;
	for (; depth <= 4; depth++) {
		if (stones[depth][index] == 0) {
			break;

		}

	}

	if (depth == 4) {
		return;

	}

	int id = 0;
	count(1, patterns[index].pattern01, &id);
	id = 0;
	count(2, patterns[index].pattern02, &id);
	id = 0;
	count(3, patterns[index].pattern03, &id);

	stones[depth][index] = 2;

}

//----------------------------------------------------------------------------------------------
int COM::pull() {
	int depth = 0;
	int index = 0;

	unsigned int probability[16]{};

	for (int i = 0; i < 16; i++) {
		probability[i] = 1;

		int id = 0;
		count(1, patterns[i].pattern01, &id, &probability[i]);
		id = 0;
		count(2, patterns[i].pattern02, &id, &probability[i]);
		id = 0;
		count(3, patterns[i].pattern03, &id, &probability[i]);

	}

	do {
		depth = 0;

		int max = 0;
		for (int i = 0; i < 16; i++) {
			max += probability[i];

		}

		int value = GetRand(max - 1);

		max = 0;
		for (int i = 0; i < 16; i++) {
			if (value <= max + probability[i]) {
				index = i;

				break;

			}

			max += probability[i];

		}

		for (; depth <= 4; depth++) {
			if (stones[depth][index] == 0) {
				break;

			}

		}

	} while (depth == 4);

	stones[depth][index] = 1;

	return index;

}

//----------------------------------------------------------------------------------------------
void COM::count(int tree, unsigned int *pattern, int *id, int j, int limit) {
	if (tree == 0) {
		int point = 64 - limit + j - 1;
		int depth = point / 16;
		int index = point % 16;

		int type = stones[depth][index];
		if (type == 1) {
			pattern[*id]++;

		}
		else if (type == 2) {
			pattern[*id + 1]++;

		}

		return;

	}

	for (int i = 0; i < limit; i++) {
		count(tree - 1, pattern, id, i, limit - 1);

		*id += 2;

	}

}

//----------------------------------------------------------------------------------------------
void COM::count(int tree, unsigned int *pattern, int *id, unsigned int *result, int j, int limit) {
	if (tree == 0) {
		int point = 64 - limit + j - 1;
		int depth = point / 16;
		int index = point % 16;

		int type = stones[depth][index];
		if (type == 1) {
			*result += pattern[*id];

		}
		else if (type == 2) {
			*result += pattern[*id + 1];

		}

		return;

	}

	for (int i = 0; i < limit; i++) {
		count(tree - 1, pattern, id, result, i, limit - 1);

		*id += 2;

	}

}