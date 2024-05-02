#define _CRT_SECURE_NO_WARNINGS

#include "Server.h"

int main() {
	setlocale(LC_ALL, "rus");

	Server server;

	server.run();	

	return 0;
}