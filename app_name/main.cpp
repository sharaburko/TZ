#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Quotes.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <memory>

int main() {
	setlocale(LC_ALL, "rus");
	//std::ofstream logs;
	//std::ofstream bars;
	//logs.open("Logs/Quotes.log", std::ios::app);
	//bars.open("Bars");

	const int sizeBuffer = 2000;
	int sizeData = 0;
	const auto buffer = std::unique_ptr<char[]>(new char[sizeBuffer]);

	auto handle = CreateServer();
	StartServer(handle);	

	//std::cout << "size: " << sizeData << std::endl;
	//std::cout << buffer << std::endl;

	//StopServer(handle);
	//DeleteServer(handle);

	//if (logs.is_open()) {
	//	std::cout << "Файл открыт\n";
	//}
	//else {
	//	std::cout << "Файл не найден\n";

	//}

	if (sizeData == -1) {
		std::cout << "Сервер не содержит данных..\n";
	}
	else {
		std::cout <<  "Данные считываются...\n";

		int count = 0;

		while (true)
		{
			memset(buffer.get(), 0, sizeBuffer);
			ReadData(handle, buffer.get(), sizeBuffer);
			std::cout << buffer;
			count++;

			if (_kbhit() || count == 3 )
			{

				if (_getch() == 3 || count == 3)
				{
					std::cout << "\nCчитывание данных прервано...\n";
					//logs.close();
					//bars.close();
					break;
				}

			}

		}

	}
	StopServer(handle);
	DeleteServer(handle);
	return 0;
}