#include "Main.h"

#include "resource.h"

#include "Box.h"

#include "Start.h"
#include "Stage.h"

#include "Connection.h"
#include "COM.h"

static Main main;

Main GetMain() {
	return main;

}

bool quit;
int state;
VECTOR sp, ep;
MV1_COLL_RESULT_POLY hp;

static int aSecond;

static Box box;

static Start start;
static Stage stage;

static Connection connection;
static COM *com;

//----------------------------------------------------------------------------------------------
void Main::init() {
	{
		SetOutApplicationLogValidFlag(false);
		ChangeWindowMode(true);
		SetMainWindowText("もくもく四目");
		SetMainWindowClassName("client");
		SetWindowIconID(ID_ICON);
	}

	if (DxLib_Init() == -1) {
		MessageBox(NULL, "初期化に失敗しました。\n複数起動することはできません。", "メッセージ", MB_OK | MB_ICONEXCLAMATION);
		quit = true;
		return;
	}
	else {
		quit = false;
	}

	{
		SetDrawScreen(DX_SCREEN_BACK);
		SetLightDirection(VGet(0.5f, -1.0f, 0.5f));
		SetUseZBuffer3D(true);
		SetWriteZBuffer3D(true);
		SetCameraNearFar(1.0f, 300.0f);
		SetDXArchiveExtension("obj");
		SetAlwaysRunFlag(true);
		SetFontSize(28);
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
		SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, GetColor(255, 0, 0));
		SetKeyInputCursorBrinkFlag(true);
	}

	{
		LONGLONG start;
		ScreenFlip();
		start = GetNowHiPerformanceCount();
		ScreenFlip();
		aSecond = (int)(1000000 / (GetNowHiPerformanceCount() - start));
	}

	{
		
		box.init();

		start.init();

	}

}

//----------------------------------------------------------------------------------------------
void Main::update() {
	switch (state) {
	case 0:
		start.update();

		break;

	case 1:
		stage.update();
		if (connection.GetState()) {
			if (connection.GetDataLength() > 0) {
				char mess[4];
				connection.recv(mess);

				int index = stoi(mess);

				stage.drop(index, 2);

			}

		}
		else {
			{
				int GHandle = MakeGraph(640, 480);
				GetMain().draw();
				GetDrawScreenGraph(0, 0, 640, 480, GHandle);

				Gui gui;
				Message mess;

				gui.init();
				mess.init("相手との通信が切れたことを確認");

				bool mouse = false;

				while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
					int mouseX, mouseY;
					GetMousePoint(&mouseX, &mouseY);
					mess.mouseMoved(mouseX, mouseY);

					if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
						mouse = true;
					}
					else {
						if (mouse) {
							if (mess.hit) {

								break;

							}

						}

						mouse = false;
					}

					mess.update();

					DrawGraph(0, 0, GHandle, false);
					gui.draw();
					mess.draw();

					ScreenFlip();

				}

				DeleteGraph(GHandle);
				gui.dispose();

				while (CheckHitKey(KEY_INPUT_ESCAPE));

			}

			ChangeState(0);

		}

		break;

	case 2:
		stage.update();
		if (!stage.turn) {
			stage.drop(com->pull(), 2);

		}

		break;

	case 3:

		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::draw() {
	box.draw();

	switch (state) {
	case 0:
		start.draw();

		break;

	case 1:
		stage.draw();

		break;

	case 2:
		stage.draw();

		break;

	case 3:

		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::dispose() {
	box.dispose();

	switch (state) {
	case 0:
		start.dispose();

		break;

	case 1:
		stage.dispose();
		connection.dispose();

		break;

	case 2:
		stage.dispose();
		delete com;

		break;

	case 3:

		break;

	}

	if (DxLib_End() == -1) {
		state = -1;

	}

}

//----------------------------------------------------------------------------------------------
void Main::keyInput(int key) {
	if (key == KEY_INPUT_ESCAPE) {
		while (CheckHitKey(KEY_INPUT_ESCAPE));

		Pause();

	}

	switch (state) {
	case 0:
		break;

	case 1:
		break;

	case 2:
		break;

	case 3:
		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::mousePressed(int x, int y, int button) {
	switch (state) {
	case 0:
		break;

	case 1:
		break;

	case 2:
		break;

	case 3:
		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::mouseReleased(int x, int y, int button) {
	switch (state) {
	case 0:
		start.mouseClicked(button);

		break;

	case 1:
		stage.mouseClicked(button);

		break;

	case 2:
		stage.mouseClicked(button);

		break;

	case 3:

		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::mouseMoved(int x, int y) {
	sp = ConvScreenPosToWorldPos(VGet((float)x, (float)y, 0.0f));
	ep = ConvScreenPosToWorldPos(VGet((float)x, (float)y, 1.0f));

	switch (state) {
	case 0:
		start.mouseMoved();

		break;

	case 1:
		stage.mouseMoved();

		break;

	case 2:
		stage.mouseMoved();

		break;

	case 3:

		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::mouseDragged(int x, int y, int button) {
	switch (state) {
	case 0:
		start.mouseDragged(x, button);

		break;

	case 1:
		stage.mouseDragged(x, y, button);

		break;

	case 2:
		stage.mouseDragged(x, y, button);

		break;

	case 3:

		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::mouseWheel(int value) {
	switch (state) {
	case 0:
		break;

	case 1:
		stage.mouseWheel(value);

		break;

	case 2:
		stage.mouseWheel(value);

		break;

	case 3:

		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::push(int index) {
	switch (state) {
	case 0:
		break;

	case 1:
		if (connection.GetState()) {
			char mess[4];
			sprintf_s(mess, 4, "%d", index);

			connection.send(mess);

		}
		else {
			{
				int GHandle = MakeGraph(640, 480);
				GetMain().draw();
				GetDrawScreenGraph(0, 0, 640, 480, GHandle);

				Gui gui;
				Message mess;

				gui.init();
				mess.init("相手との通信が切れたことを確認");

				bool mouse = false;

				while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
					int mouseX, mouseY;
					GetMousePoint(&mouseX, &mouseY);
					mess.mouseMoved(mouseX, mouseY);

					if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
						mouse = true;
					}
					else {
						if (mouse) {
							if (mess.hit) {
								break;

							}

						}

						mouse = false;
					}

					mess.update();

					DrawGraph(0, 0, GHandle, false);
					gui.draw();
					mess.draw();

					ScreenFlip();

				}

				DeleteGraph(GHandle);
				gui.dispose();

				while (CheckHitKey(KEY_INPUT_ESCAPE));

			}

			ChangeState(0);

		}

		break;

	case 2:
		com->push(index);

		break;

	case 3:


		break;

	}

}

//----------------------------------------------------------------------------------------------
void Main::pull() {
	switch (state) {
	case 0:
		break;

	case 1:
		connection.send("cont");

		{
			int GHandle = MakeGraph(640, 480);
			GetMain().draw();
			GetDrawScreenGraph(0, 0, 640, 480, GHandle);

			Gui gui;
			Message mess;
			Message ten;

			gui.init();
			mess.init("相手の出方次第だ", 180, GetColor(10, 10, 10));
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

				if (connection.GetState()) {
					if (connection.GetDataLength() > 0) {
						char mess[4];
						connection.recv(mess);

						if (strcmp(mess, "cont")) {
							return;

						}

					}
					
				}
				else {
					{
						int GHandle = MakeGraph(640, 480);
						GetMain().draw();
						GetDrawScreenGraph(0, 0, 640, 480, GHandle);

						Gui gui;
						Message mess;

						gui.init();
						mess.init("相手との通信が切れたことを確認");

						bool mouse = false;

						while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
							int mouseX, mouseY;
							GetMousePoint(&mouseX, &mouseY);
							mess.mouseMoved(mouseX, mouseY);

							if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
								mouse = true;
							}
							else {
								if (mouse) {
									if (mess.hit) {
										break;

									}

								}

								mouse = false;
							}

							mess.update();

							DrawGraph(0, 0, GHandle, false);
							gui.draw();
							mess.draw();

							ScreenFlip();

						}

						gui.dispose();

						while (CheckHitKey(KEY_INPUT_ESCAPE));

					}

					break;

				}

				WaitTimer(2000);

			}

			DeleteGraph(GHandle);
			gui.dispose();

			while (CheckHitKey(KEY_INPUT_ESCAPE));

		}

		ChangeState(0);

		break;

	case 2:
		Stage::resetStones(com->stones);

		break;

	case 3:


		break;

	}

}

//----------------------------------------------------------------------------------------------
void ChangeState(int changedState) {
	if (state == changedState) {
		return;

	}

	switch (state) {
	case 0:
		start.dispose();

		break;

	case 1:
		stage.dispose();
		connection.dispose();

		break;

	case 2:
		stage.dispose();
		delete com;

		break;

	case 3:

		break;

	}

	switch (changedState) {
	case 0:
		start.init();

		break;

	case 1:
		stage.init(start.pvp.client);
		connection.init(start.pvp.partner);

		break;

	case 2:
		stage.init(true);
		com = new COM();

		break;

	case 3:

		break;

	}

	state = changedState;

}

//----------------------------------------------------------------------------------------------
int GetInterval(int millis) {
	return (int)(aSecond * millis / 1000.0f);

}

//----------------------------------------------------------------------------------------------
float GetRedian(float si) {
	return (si * DX_PI / 180);

}

//----------------------------------------------------------------------------------------------
void Pause() {
	switch (state) {
	case 0://スタート画面
		quit = true;

		break;

	case 1://PvP
	case 2://PvC
	{
		int GHandle = MakeGraph(640, 480);
		GetMain().draw();
		GetDrawScreenGraph(0, 0, 640, 480, GHandle);

		Gui gui;
		Message mess;
		Yes yes;
		No no;

		gui.init();
		mess.init("対戦を終了しますか？", 180, GetColor(120, 250, 120), GetColor(0, 0, 0));
		yes.init();
		no.init();

		bool mouse = false;

		while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
			int mouseX, mouseY;
			GetMousePoint(&mouseX, &mouseY);
			yes.mouseMoved(mouseX, mouseY);
			no.mouseMoved(mouseX, mouseY);

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				mouse = true;
			}
			else {
				if (mouse) {
					if (yes.hit) {
						ChangeState(0);

						break;

					}
					else if (no.hit) {
						break;

					}

				}

				mouse = false;
			}

			yes.update();
			no.update();

			DrawGraph(0, 0, GHandle, false);
			gui.draw();
			mess.draw();
			yes.draw();
			no.draw();

			ScreenFlip();

		}

		DeleteGraph(GHandle);
		gui.dispose();
		yes.dispose();
		no.dispose();

		while (CheckHitKey(KEY_INPUT_ESCAPE));

	}

		break;

	case 3://CvC
		break;

	}
}