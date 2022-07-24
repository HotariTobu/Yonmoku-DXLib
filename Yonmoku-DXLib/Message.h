#pragma once

#include "Main.h"

class Message {
public:
	void init(const TCHAR *text, int y = 180, int core = GetColor(240, 180, 0), int edge = GetColor(255, 255, 255), int seleCore = GetColor(0, 120, 160), int seleEdge = GetColor(255, 255, 255));
	void update();
	void draw();

	void mouseMoved(int x, int y);

	void SetText(const TCHAR *text);
	void SetY(int y);
	void SetCoreColor(int core);
	void SetEdgeColor(int edge);
	void SetSeleCoreColor(int seleCore);
	void SetSeleEdgeColor(int SeleEdge);

	bool hit;

private:
	const TCHAR *text;
	int x, y;
	int width, height;
	int core, edge, seleCore, seleEdge, drawCore, drawEdge;

};