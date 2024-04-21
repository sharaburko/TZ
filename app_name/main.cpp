#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Quotes.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <memory>
#include <Windows.h>
#include "Bar.h"




int main() {
	setlocale(LC_ALL, "rus");
	//std::ofstream logs;
	//std::ofstream bars;
	//logs.open("Logs/Quotes.log", std::ios::app);
	//bars.open("Bars");

	SYSTEMTIME time;
	
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
		GetLocalTime(&time);
		std::cout << std::endl << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << std::endl;
		std::cout <<  "Данные считываются...\n\n";

		const int start = time.wMinute;
		for(size_t i = 0; i < 1; i++)
		{
			
			GetLocalTime(&time);			
			if (start == time.wMinute) {
				memset(buffer.get(), 0, sizeBuffer);
				int bufSize = ReadData(handle, buffer.get(), sizeBuffer);

				for(int i = 0; i < bufSize; i++)

				std::cout << buffer[i];
				
			}
			

			if (_kbhit() )
			{

				if (_getch() == 3)
				{					
					//logs.close();
					//bars.close();
					std::cout << "\nCчитывание данных прервано пользователем.\n";
					break;
				}

			}

		}

	}
	GetLocalTime(&time);
	std::cout << std::endl << std::endl  << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << std::endl;
	std::cout << "Cчитывание данных окончено\n";
	StopServer(handle);
	DeleteServer(handle);
	return 0;
}