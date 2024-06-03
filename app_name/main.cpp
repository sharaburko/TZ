#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"

BOOL HandlerRoutine(DWORD dwCtrlType);
Server server;

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)HandlerRoutine, true);
	server.run();
	return 0;
}

BOOL HandlerRoutine(DWORD dwCtrlType) {

	if (dwCtrlType == CTRL_C_EVENT) {
		Beep(750, 300);
		server.stop_loop();
		//system("pause");
		return 1;
	}

	return 0;
}