#include "Connection.h"

//----------------------------------------------------------------------------------------------
void Connection::init(int NHandle) {
	this->NHandle = NHandle;

}

//----------------------------------------------------------------------------------------------
void Connection::dispose() {
	CloseNetWork(NHandle);

}

//----------------------------------------------------------------------------------------------
bool Connection::GetState() {
	return GetNetWorkAcceptState(NHandle);

}

//----------------------------------------------------------------------------------------------
int Connection::GetDataLength() {
	return GetNetWorkDataLength(NHandle);

}

//----------------------------------------------------------------------------------------------
void Connection::send(char *mess) {
	NetWorkSend(NHandle, mess, sizeof(mess) * sizeof(char));

}

//----------------------------------------------------------------------------------------------
void Connection::recv(char *mess) {
	NetWorkRecv(NHandle, mess, sizeof(mess) * sizeof(char));

}

//----------------------------------------------------------------------------------------------
bool Connection::CheckIP(string ipStr, IPDATA *ip) {
	int ds[4];

	try {
		int n = 0;
		for (int i = 0; i < ipStr.length(); i++) {
			if (ipStr.at(i) == '.') {
				n++;
			}
		}

		if (n != 3) {
			throw - 1;
		}

		int start = 0;
		int off = ipStr.find('.', 0);
		ip->d1 = stoi(ipStr.substr(start, off));
		start = ++off;
		off = ipStr.find('.', start);
		ip->d2 = stoi(ipStr.substr(start, off));
		start = ++off;
		off = ipStr.find('.', start);
		ip->d3 = stoi(ipStr.substr(start, off));
		start = ++off;
		off = ipStr.find('.', start);
		ip->d4 = stoi(ipStr.substr(start, off));

	}
	catch (...) {
		return false;
	}

	return true;

}