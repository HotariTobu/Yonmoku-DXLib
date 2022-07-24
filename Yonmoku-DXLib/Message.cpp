#include"Message.h"

//----------------------------------------------------------------------------------------------
void Message::init(const TCHAR *text, int y, int core, int edge, int seleCore, int seleEdge) {
	this->text = text;

	hit = false;

	GetDrawStringSize(&width, &height, NULL, text, GetStringLength(text));

	x = (640 - width) / 2;
	this->y = y;

	this->core = core;
	this->edge = edge;
	this->seleCore = seleCore;
	this->seleEdge = seleEdge;
	this->drawCore = core;
	this->drawEdge = edge;

}

//----------------------------------------------------------------------------------------------
void Message::update() {
	if (hit) {
		this->drawCore = seleCore;
		this->drawEdge = seleEdge;
	}
	else {
		this->drawCore = core;
		this->drawEdge = edge;
	}

}

//----------------------------------------------------------------------------------------------
void Message::draw() {
	DrawString(x, y, text, drawCore, drawEdge);

}

//----------------------------------------------------------------------------------------------
void Message::mouseMoved(int x, int y) {
	hit = (this->x < x && this->x + width > x) && (this->y < y && this->y + height > y);

}

//----------------------------------------------------------------------------------------------
void Message::SetText(const TCHAR *text) {
	this->text = text;

	GetDrawStringSize(&width, &height, NULL, text, GetStringLength(text));

	x = (640 - width) / 2;

}

//----------------------------------------------------------------------------------------------
void Message::SetY(int y) {
	this->y = y;

}

//----------------------------------------------------------------------------------------------
void Message::SetCoreColor(int core) {
	this->core = core;

}

//----------------------------------------------------------------------------------------------
void Message::SetEdgeColor(int edge) {
	this->edge = edge;

}

//----------------------------------------------------------------------------------------------
void Message::SetSeleCoreColor(int seleCore) {
	this->seleCore = seleCore;

}

//----------------------------------------------------------------------------------------------
void Message::SetSeleEdgeColor(int SeleEdge) {
	this->seleEdge = seleEdge;

}