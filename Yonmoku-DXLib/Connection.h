#pragma once

#include "Main.h"

class Connection {
public :
	void init(int NHandle);
	void dispose();

	bool GetState();
	int GetDataLength();

	void send(char *mess);
	void recv(char *mess);

	static bool CheckIP(string ipStr, IPDATA *ip);

private :
	int NHandle;

};