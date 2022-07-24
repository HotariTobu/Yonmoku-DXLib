#include"Main.h"

static int lastMouseX, lastMouseY;
static bool mouse = false;
static int lastMouseButton;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	GetMain().init();

	while (!ProcessMessage() && !ClearDrawScreen() && !quit) {
		{
			char keys[256];
			GetHitKeyStateAll(keys);
			for (int i = 0; i < 256; i++) {
				if (keys[i]) {
					GetMain().keyInput(i);
				}
			}
		}

		int nowMouseX, nowMouseY;
		GetMousePoint(&nowMouseX, &nowMouseY);
		int mouseButton = GetMouseInput();

		{
			if ((mouseButton & MOUSE_INPUT_LEFT) != 0) {
				mouseButton = MOUSE_INPUT_LEFT;
			}
			else if ((mouseButton & MOUSE_INPUT_RIGHT) != 0) {
				mouseButton = MOUSE_INPUT_RIGHT;
			}
			else if ((mouseButton & MOUSE_INPUT_MIDDLE) != 0) {
				mouseButton = MOUSE_INPUT_MIDDLE;
			}
			else {
				mouseButton = 0;
			}

			if (mouseButton == 0) {
				if (mouse) {
					GetMain().mouseReleased(nowMouseX, nowMouseY, lastMouseButton);
				}

				mouse = false;
			}
			else {
				if (!mouse) {
					GetMain().mousePressed(nowMouseX, nowMouseY, mouseButton);

					lastMouseButton = mouseButton;
				}

				mouse = true;
			}
		}

		{
			if (lastMouseX != nowMouseX || lastMouseY != nowMouseY) {
				GetMain().mouseMoved(nowMouseX, nowMouseY);

				GetMain().mouseDragged(lastMouseX - nowMouseX, lastMouseY - nowMouseY, mouseButton);
			}
			GetMousePoint(&lastMouseX, &lastMouseY);
		}

		GetMain().mouseWheel(GetMouseWheelRotVol());

		GetMain().update();

		GetMain().draw();

		GetMousePoint(&lastMouseX, &lastMouseY);

		ScreenFlip();
	}

	GetMain().dispose();

	return 0;
}