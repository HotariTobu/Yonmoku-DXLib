#include "PvP.h"

#include "Connection.h"

//----------------------------------------------------------------------------------------------
void PvP::init() {
	hit = false;
	model = MV1LoadModel("impo/PvP.mqo");
	MV1SetupCollInfo(model);

	MV1SetPosition(model, VGet(0, 0, 10));

	rotate = 0.0f;
	rotateFrame = 0;
	rotateDelimit = GetInterval(50);
}

//----------------------------------------------------------------------------------------------
void PvP::update() {
	rotateFrame++;

	if (rotateFrame == rotateDelimit) {
		if (hit) {
			rotate -= 2.5f;
		}
		else {
			rotate -= 0.5f;
		}

		rotateFrame = 0;
	}

	MV1SetRotationXYZ(model, VGet(0.0f, GetRedian(rotate), 0.0f));

}

//----------------------------------------------------------------------------------------------
void PvP::draw() {
	MV1DrawModel(model);
}

//----------------------------------------------------------------------------------------------
void PvP::dispose() {
	MV1DeleteModel(model);
}

//----------------------------------------------------------------------------------------------
void PvP::mouseClicked(int button) {
	if (hit && button == MOUSE_INPUT_LEFT) {
		IPDATA ip;

		{
			int GHandle = MakeGraph(640, 480);
			GetMain().draw();
			GetDrawScreenGraph(0, 0, 640, 480, GHandle);

			Gui gui;
			Message mess;
			Input input;
			Message nou;
			Message ju;
			Cancel cancel;

			gui.init();
			mess.init("ëäéËÇÃIPÉAÉhÉåÉXÇì¸óÕ", 140, GetColor(10, 10, 10));
			input.init(15, 170);
			nou.init("ê⁄ë±Ç∑ÇÈ", 220);
			ju.init("ê⁄ë±Ç≥ÇÍÇÈ", 260);
			cancel.init();

			bool mouse = false;

	while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		input.mouseMoved(mouseX, mouseY);
		nou.mouseMoved(mouseX, mouseY);
		ju.mouseMoved(mouseX, mouseY);
		cancel.mouseMoved(mouseX, mouseY);

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			mouse = true;
		}
		else {
			if (mouse) {
				input.mouseClicked(MOUSE_INPUT_LEFT);

				if (nou.hit) {
					client = true;

					if (Connection::CheckIP(input.text, &ip)) {
						break;
					}
					else {
						mess.SetText("ñ≥å¯Ç≈Ç∑");
					}

				}
				else if (ju.hit) {
					client = false;
					
					if (Connection::CheckIP(input.text, &ip)) {
						break;
					}
					else {
						mess.SetText("ñ≥å¯Ç≈Ç∑");
					}


				}
				else if (cancel.hit) {
					return;
				}

			}

			mouse = false;
		}

		input.update();
		nou.update();
		ju.update();
		cancel.update();

		DrawGraph(0, 0, GHandle, false);
		gui.draw();
		mess.draw();
		input.draw();
		nou.draw();
		ju.draw();
		cancel.draw();

		ScreenFlip();

	}

	DeleteGraph(GHandle);
gui.dispose();
input.dispose();
cancel.dispose();

while (CheckHitKey(KEY_INPUT_ESCAPE));

		}

		int net;

		if (!client) {
			PreparationListenNetWork(54069);

		}

		{
		int GHandle = MakeGraph(640, 480);
		GetMain().draw();
		GetDrawScreenGraph(0, 0, 640, 480, GHandle);

		Gui gui;
		Message mess;
		Message ten;

		gui.init();
		mess.init("Ç»Ç§Ç±ÇÀÇ≠ÇƒÇ°ÇÒÇÆ", 180, GetColor(10, 10, 10));
		ten.init("---", 220, GetColor(0, 200, 0));

		int messageNumber = 0;

		while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
			messageNumber++;

			if (messageNumber == 4) {
				messageNumber = 0;
			}

			switch (messageNumber) {
			case 0:
				ten.SetText("---");
				break;
			case 1:
				ten.SetText("<--");
				break;
			case 2:
				ten.SetText("-|-");
				break;
			case 3:
				ten.SetText("-->");
				break;
			}

			DrawGraph(0, 0, GHandle, false);
			gui.draw();
			mess.draw();
			ten.draw();

			ScreenFlip();

			if (client) {
				net = ConnectNetWork(ip, 54069);
				if (net != -1) {
					this->partner = net;

					ChangeState(1);

					break;

				}

			}
			else {
				net = GetNewAcceptNetWork();
				if (net != -1) {
					this->partner = net;

					StopListenNetWork();
					ChangeState(1);

					break;

				}

				WaitTimer(2000);

			}

		}

		DeleteGraph(GHandle);
		gui.dispose();

		while (CheckHitKey(KEY_INPUT_ESCAPE));

}

	}
}

//----------------------------------------------------------------------------------------------
void PvP::mouseMoved() {
	MV1RefreshCollInfo(model, -1);

	hp = MV1CollCheck_Line(model, -1, sp, ep);

	hit = hp.HitFlag;
	if (hit) {
		MV1SetEmiColorScale(model, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else {
		MV1SetEmiColorScale(model, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
}