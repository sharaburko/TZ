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

	auto handle = CreateServer();

	StartServer(handle);
	const int sizeBuffer = 2000;
	const auto buffer  = std::unique_ptr<char []>(new char[sizeBuffer]);
	memset(buffer.get(), 0, sizeBuffer);
	
	
	int sizeData = ReadData(handle, buffer.get(), sizeBuffer);
	std::cout << "size: " << sizeData << std::endl;
	std::cout << buffer << std::endl;




	StopServer(handle);
	DeleteServer(handle);


	//if (logs.is_open()) {
	//	std::cout << "Файл открыт\n";
	//}
	//else {
	//	std::cout << "Файл не найден\n";

	//}

	////int x = _getch();
	////std::cout << x << std::endl;

	////if (sizeData == -1) {
	////	logs << "Сервер не содержит данных..\n";
	////}
	////else {
	////	logs << "Данные считаны...\n";
	////}

	//while (true)
	//{
	//	if (_kbhit()) {
	//		if (_getch() == 3) {
	//			delete[] buffer;

	//			StopServer(Server);
	//			DeleteServer(Server);

	//			logs.close();
	//			bars.close();
	//			return 0;
	//			break;
	//		}
	//	}
	//	int sizeData; ReadData(Server, buffer, size);
	//	//std::cout << ReadData(Server, buffer, size) << std::endl;
	//	std::cout << buffer << std::endl;
	//}



}