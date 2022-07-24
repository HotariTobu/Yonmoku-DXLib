#include"Stage.h"

//----------------------------------------------------------------------------------------------
void Stage::init(bool turn) {
	stand.init();
	stone.init();

	distance = 100;
	angleH = 0;
	angleV = -30;

	this->turn = turn;

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, (float)distance), VGet(0, 0, 0));
	GetMouseWheelRotVol();

	resetStones();

}

//----------------------------------------------------------------------------------------------
void Stage::update() {
	cameraX = 0;
	cameraY = 0;
	cameraZ = (float)distance;

	rotate(&cameraY, &cameraZ, angleV);
	rotate(&cameraZ, &cameraX, -angleH);

	SetCameraPositionAndTarget_UpVecY(VGet(cameraX, cameraY, cameraZ), VGet(0, 0, 0));

	stand.update();

	int index = stand.index - 1;
	if (index >= 0 && turn && stones[3][index] == 0) {
		stone.SetOpacity(0.8f);
		stone.update({ (index / 4 * 2 - 3)*6.25f ,13.6f,(index % 4 * -2 + 3)*6.25f }, 1);
		stone.draw();
		stone.SetOpacity(1.0f);

	}

}

//----------------------------------------------------------------------------------------------
void Stage::draw() {
	stand.draw();

	for (int depth = 0; depth < 4; depth++) {
		for (int point = 0; point < 16; point++) {
			int type = stones[depth][point];

			if (type != 0) {
				stone.update({ (point / 4 * 2 - 3)*6.25f,(depth - 2)*6.9f - 0.2f,(point % 4 * -2 + 3)*6.25f, }, type);
				stone.draw();

			}

		}

	}

}

//----------------------------------------------------------------------------------------------
void Stage::dispose() {
	stand.dispose();
	stone.dispose();

}

//----------------------------------------------------------------------------------------------
void Stage::mouseClicked(int button) {
	if (stand.hit && button == MOUSE_INPUT_LEFT) {
		int index = stand.index - 1;

		if (index >= 0 && turn) {
			GetMain().push(index);

			drop(index, 1);

		}

	}

}

//----------------------------------------------------------------------------------------------
void Stage::mouseMoved() {
	stand.mouseMoved();

}

//----------------------------------------------------------------------------------------------
void Stage::mouseDragged(int x, int y, int button) {
	if (button == MOUSE_INPUT_RIGHT) {
		angleH += x;
		angleV += y;

		angleH = angleH % 360;

		if (angleV < -89) {
			angleV = -89;
		}
		else if (angleV > 89) {
			angleV = 89;
		}

	}

}

//----------------------------------------------------------------------------------------------
void Stage::mouseWheel(int value) {
	distance -= value * 10;

	if (distance < 30) {
		distance = 30;
	}
	else if (distance > 100) {
		distance = 100;
	}

}

//----------------------------------------------------------------------------------------------
void Stage::resetStones() {
	resetStones(stones);
}

//----------------------------------------------------------------------------------------------
void Stage::resetStones(int stones[4][16]) {
	for (int depth = 0; depth < 4; depth++) {
		for (int point = 0; point < 16; point++) {
			stones[depth][point] = 0;

		}

	}

}

//----------------------------------------------------------------------------------------------
int Stage::CheckLine() {
	return CheckLine(stones);
}

//----------------------------------------------------------------------------------------------
int Stage::CheckLine(int stones[4][16]) {
	int winner = 0;

	for (int i = 0; i < 4 && winner == 0; i++) {
		for (int j = 0; j < 16 && winner == 0; j += 4) {
			if (stones[i][j] != 0 &&
				stones[i][j] == stones[i][j + 1] &&
				stones[i][j + 1] == stones[i][j + 2] &&
				stones[i][j + 2] == stones[i][j + 3]
				) {

				winner = stones[i][j];

				stones[i][j] = 3;
				stones[i][j + 1] = 3;
				stones[i][j + 2] = 3;
				stones[i][j + 3] = 3;
			}
		}
	}

	for (int i = 0; i < 4 && winner == 0; i++) {
		for (int j = 0; j < 4 && winner == 0; j++) {
			if (stones[i][j] != 0 &&
				stones[i][j] == stones[i][j + 4] &&
				stones[i][j + 4] == stones[i][j + 8] &&
				stones[i][j + 8] == stones[i][j + 12]
				) {

				winner = stones[i][j];

				stones[i][j] = 3;
				stones[i][j + 4] = 3;
				stones[i][j + 8] = 3;
				stones[i][j + 12] = 3;
			}
		}
	}

	for (int i = 0; i < 16 && winner == 0; i++) {
		if (stones[0][i] != 0 &&
			stones[0][i] == stones[1][i] &&
			stones[1][i] == stones[2][i] &&
			stones[2][i] == stones[3][i]
			) {

			winner = stones[0][i];

			stones[0][i] = 3;
			stones[1][i] = 3;
			stones[2][i] = 3;
			stones[3][i] = 3;
		}
	}

	for (int i = 0; i < 4 && winner == 0; i++) {
		if (stones[i][0] != 0 &&
			stones[i][0] == stones[i][5] &&
			stones[i][5] == stones[i][10] &&
			stones[i][10] == stones[i][15]
			) {

			winner = stones[i][0];

			stones[i][0] = 3;
			stones[i][5] = 3;
			stones[i][10] = 3;
			stones[i][15] = 3;
		}
	}

	for (int i = 0; i < 4 && winner == 0; i++) {
		if (stones[i][12] != 0 &&
			stones[i][12] == stones[i][9] &&
			stones[i][9] == stones[i][6] &&
			stones[i][6] == stones[i][3]
			) {

			winner = stones[i][12];

			stones[i][12] = 3;
			stones[i][9] = 3;
			stones[i][6] = 3;
			stones[i][3] = 3;
		}
	}

	for (int i = 0; i < 16 && winner == 0; i += 4) {
		if (stones[0][i] != 0 &&
			stones[0][i] == stones[1][i + 1] &&
			stones[1][i + 1] == stones[2][i + 2] &&
			stones[2][i + 2] == stones[3][i + 3]
			) {

			winner = stones[0][i];

			stones[0][i] = 3;
			stones[1][i + 1] = 3;
			stones[2][i + 2] = 3;
			stones[3][i + 3] = 3;
		}
	}

	for (int i = 3; i < 16 && winner == 0; i += 4) {
		if (stones[0][i] != 0 &&
			stones[0][i] == stones[1][i - 1] &&
			stones[1][i - 1] == stones[2][i - 2] &&
			stones[2][i - 2] == stones[3][i - 3]
			) {

			winner = stones[0][i];

			stones[0][i] = 3;
			stones[1][i - 1] = 3;
			stones[2][i - 2] = 3;
			stones[3][i - 3] = 3;
		}
	}

	for (int i = 0; i < 4 && winner == 0; i++) {
		if (stones[0][i] != 0 &&
			stones[0][i] == stones[1][i + 4] &&
			stones[1][i + 4] == stones[2][i + 8] &&
			stones[2][i + 8] == stones[3][i + 12]
			) {

			winner = stones[0][i];

			stones[0][i] = 3;
			stones[1][i + 4] = 3;
			stones[2][i + 8] = 3;
			stones[3][i + 12] = 3;
		}
	}

	for (int i = 12; i < 16 && winner == 0; i++) {
		if (stones[0][i] != 0 &&
			stones[0][i] == stones[1][i - 4] &&
			stones[1][i - 4] == stones[2][i - 8] &&
			stones[2][i - 8] == stones[3][i - 12]
			) {

			winner = stones[0][i];

			stones[0][i] = 3;
			stones[1][i - 4] = 3;
			stones[2][i - 8] = 3;
			stones[3][i - 12] = 3;
		}
	}

	if (winner == 0 &&
		stones[0][0] != 0 &&
		stones[0][0] == stones[1][5] &&
		stones[1][5] == stones[2][10] &&
		stones[2][10] == stones[3][15]
		) {

		winner = stones[0][0];

		stones[0][0] = 3;
		stones[1][5] = 3;
		stones[2][10] = 3;
		stones[3][15] = 3;
	}

	if (winner == 0 &&
		stones[0][15] != 0 &&
		stones[0][15] == stones[1][10] &&
		stones[1][10] == stones[2][5] &&
		stones[2][5] == stones[3][0]
		) {

		winner = stones[0][15];

		stones[0][15] = 3;
		stones[1][10] = 3;
		stones[2][5] = 3;
		stones[3][0] = 3;
	}

	if (winner == 0 &&
		stones[0][12] != 0 &&
		stones[0][12] == stones[1][9] &&
		stones[1][9] == stones[2][6] &&
		stones[2][6] == stones[3][3]
		) {

		winner = stones[0][12];

		stones[0][12] = 3;
		stones[1][9] = 3;
		stones[2][6] = 3;
		stones[3][3] = 3;
	}

	if (winner == 0 &&
		stones[0][3] != 0 &&
		stones[0][3] == stones[1][6] &&
		stones[1][6] == stones[2][9] &&
		stones[2][9] == stones[3][12]
		) {

		winner = stones[0][3];

		stones[0][3] = 3;
		stones[1][6] = 3;
		stones[2][9] = 3;
		stones[3][12] = 3;
	}

	if (winner == 0) {
		bool te = true;

		for (int i = 0; i < 4 && te; i++) {
			for (int j = 0; j < 16 && te; j++) {
				if (stones[i][j] == 0) {
					te = false;
				}
			}
		}

		if (te) {
			winner = 3;
		}
	}

	return winner;

}

//----------------------------------------------------------------------------------------------
void Stage::drop(int index, int type) {
	int depth = 0;
	for (; depth <= 4; depth++) {
		if (stones[depth][index] == 0) {
			break;

		}

	}

	if (depth == 4) {
		return;

	}

	if (type == 1) {
		turn = false;

	}
	else if (type == 2) {
		turn = true;

	}

	float x = (index / 4 * 2 - 3)*6.25f;
	float nowY = 13.6f;
	float y = (depth - 2)*6.9f - 0.2f;
	float z = (index % 4 * -2 + 3)*6.25f;

	{
		int frame = 0;
		int delimit = GetInterval(100);

		while (!ProcessMessage() && !ClearDrawScreen()) {
			if (frame == delimit) {
				nowY -= 3;

				if (nowY <= y) {
					nowY = y;

					stones[depth][index] = type;

					break;

				}

				frame = 0;
			}

			frame++;

			GetMain().draw();

			stone.update({ x,nowY,z, }, type);

			stone.draw();

			ScreenFlip();

		}

	}

	int winner = CheckLine();
	if (winner != 0) {
		bool ue = false;

		{
			int GHandle = MakeGraph(640, 480);
			GetMain().draw();
			GetDrawScreenGraph(0, 0, 640, 480, GHandle);

			Gui gui;
			Message mess;
			Message con;
			Message qu;
			Yes yes;
			No no;

			gui.init();

			switch (winner) {
			case 1:
				mess.init("WINNER", 140, GetColor(10, 10, 10));

				break;

			case 2:
				mess.init("LOSER", 140, GetColor(10, 10, 10));

				break;

			case 3:
				mess.init("DRAW", 140, GetColor(10, 10, 10));

				break;

			}

			con.init("確認");
			qu.init("こんてにゅー？", 260, GetColor(180, 200, 250), GetColor(10, 10, 10));
			yes.init();
			no.init();

			int frame = 0;
			int delimit = GetInterval(100);
			bool bright = true;

			bool mouse = false;

			while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
				int mouseX, mouseY;
				GetMousePoint(&mouseX, &mouseY);
				con.mouseMoved(mouseX, mouseY);
				yes.mouseMoved(mouseX, mouseY);
				no.mouseMoved(mouseX, mouseY);

				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
					mouse = true;
				}
				else {
					if (mouse) {
						if (con.hit) {
							{
								int lastMouseX = 0, lastMouseY = 0;

								while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
									int nowMouseX, nowMouseY;
									GetMousePoint(&nowMouseX, &nowMouseY);
									if ((lastMouseX != nowMouseX || lastMouseY != nowMouseY) && (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
										mouseDragged(lastMouseX - nowMouseX, lastMouseY - nowMouseY, MOUSE_INPUT_RIGHT);
									}
									GetMousePoint(&lastMouseX, &lastMouseY);
									
									mouseWheel(GetMouseWheelRotVol());

									cameraX = 0;
									cameraY = 0;
									cameraZ = (float)distance;

									rotate(&cameraY, &cameraZ, angleV);
									rotate(&cameraZ, &cameraX, -angleH);

									SetCameraPositionAndTarget_UpVecY(VGet(cameraX, cameraY, cameraZ), VGet(0, 0, 0));

									GetMain().draw();

									ScreenFlip();

								}

								while (CheckHitKey(KEY_INPUT_ESCAPE));

							}

							GetMain().draw();
							GetDrawScreenGraph(0, 0, 640, 480, GHandle);

						}
						else if (yes.hit) {
							ue = true;

							break;


						}
						else if (no.hit) {
							ue = false;

							break;

						}

					}

					mouse = false;
				}

				if (frame == delimit) {
					if (bright) {
						switch (winner) {
						case 1:
							mess.SetCoreColor(GetColor(255, 0, 0));

							break;

						case 2:
							mess.SetCoreColor(GetColor(0, 0, 255));

							break;

						case 3:
							mess.SetCoreColor(GetColor(0, 255, 0));

							break;

						}

					}
					else {
						mess.SetCoreColor(GetColor(10, 10, 10));

					}

					bright = !bright;

					frame = 0;

				}

				frame++;

				mess.update();
				con.update();
				yes.update();
				no.update();

				DrawGraph(0, 0, GHandle, false);
				gui.draw();
				mess.draw();
				con.draw();
				qu.draw();
				yes.draw();
				no.draw();

				ScreenFlip();

			}

			gui.dispose();
			yes.dispose();
			no.dispose();

			while (CheckHitKey(KEY_INPUT_ESCAPE));

		}

		if (ue) {
			resetStones();

			GetMain().pull();

		}
		else {
			ChangeState(0);

		}

	}

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	GetMain().mouseMoved(mouseX, mouseY);

}

//----------------------------------------------------------------------------------------------
void Stage::rotate(float *x, float *y, const int ang) {
	const float ox = *x, oy = *y;
	const double chnang = GetRedian(ang);
	*x = (float)(ox * cos(chnang) - oy * sin(chnang));
	*y = (float)(ox * sin(chnang) + oy * cos(chnang));
}