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

	SYSTEMTIME time;
	Server server;
	Logs logs("Logs");

	int start;
	const int sizeBuffer = 2000;
	int sizeData = 0;
	const auto buffer = std::unique_ptr<char[]>(new char[sizeBuffer]);

	std::ofstream of("temp.txt", std::ios::app);
	std::ifstream in;
	//std::vector <Bar> bars;
	GetLocalTime(&time);
	std::cout << std::endl << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << std::endl;
	std::cout << "Data is being read...\n\n";
	logs.AddAnEvent("Data is being read...");
	auto path = std::filesystem::current_path();
	std::cout << path << "/n";

	start = time.wMinute;
	while(true)	{
		
		GetLocalTime(&time);			

		if (start == time.wMinute) {
			memset(buffer.get(), 0, sizeBuffer);
			int sizeData = ReadData(server.getHandle(), buffer.get(), sizeBuffer);

			if (sizeData == -1) {
				std::cout << "The server does not contain data.\n";
				break;
			}
			else
			{
				of.write(buffer.get(), sizeData);
			}

		}
		else {
			of.close();
			std::cout << "\nData reading for one minute is completed.\n";
			break;
		}			

		if(isStopReadingData())
		{
			break;
		}


	}

	//in.open("temp.txt");
	//Bar tempBar;

	//while (true) {


	//	if (in.eof()) {
	//		std::cout << "\nФайл считан.\n";
	//		in.close();
	//		break;
	//	}

	//	in >> tempBar;
	//	bars.push_back(tempBar);
	//}

	GetLocalTime(&time);
	std::cout << std::endl << std::endl  << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << std::endl;
	std::cout << "Cчитывание данных окончено\n";

	return 0;
}

bool isStopReadingData()
{
	if (_kbhit())
	{

		if (_getch() == 3)
		{
			std::cout << "\nCчитывание данных прервано пользователем.\n";
			return  true;
		}

	}

	return false;

}