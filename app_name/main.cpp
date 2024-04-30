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

	std::ofstream writeBuffer("Temp/temp.txt", std::ios::app);

	for (size_t i = 0; i < 10; i++)
	{
		memset(buffer.get(), 0, sizeBuffer);
		int sizeData = ReadData(server.getHandle(), buffer.get(), sizeBuffer);

		if (sizeData == -1) {
			server.addEventToLog("The server does not contain data.");
			break;
		}
		else
		{
			writeBuffer.write(buffer.get(), sizeData);
		}

		//if (isStopReadingData())
		//{
		//	server.addEventToLog("Data reading was interrupted by the user.");
		//	writeBuffer.close();
		//	break;
		//}

	}

	server.stop();

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