#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <memory>
#include <Windows.h>
#include "Bar.h"
#include <vector>
#include "Server.h"
#include "Logs.h"
#include <filesystem>

bool isStopReadingData();

int main() {
	setlocale(LC_ALL, "rus");


	Server server;

	server.start();

	const int sizeBuffer = 2000;
	int sizeData = 0;
	const auto buffer = std::unique_ptr<char[]>(new char[sizeBuffer]);

	std::ofstream of("Temp/temp.txt", std::ios::app);

	while (true) {

		memset(buffer.get(), 0, sizeBuffer);
		int sizeData = ReadData(server.getHandle(), buffer.get(), sizeBuffer);

		if (sizeData == -1) {
			server.addEventToLog("The server does not contain data.");
			break;
		}
		else
		{
			of.write(buffer.get(), sizeData);
		}

		if (isStopReadingData())
		{
			server.addEventToLog("Data reading was interrupted by the user.");
			break;
		}

	}

	of.close();
	server.addEventToLog("Data reading for one minute is completed");

	return 0;
}

bool isStopReadingData()
{
	if (_kbhit())
	{

		if (_getch() == 3)
		{
			return  true;
		}

	}

	return false;

}