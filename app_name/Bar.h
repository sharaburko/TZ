#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include "Logs.h"
#include <unordered_map>

namespace fs = std::filesystem;

class Bar
{
private:
	std::unordered_map<std::string, std::vector <double>> map;
	std::string timeAndDateRead;
	//std::string exchangeRates;
	//std::string sign;
	//std::string time;
	//double price;
	//int size;

	std::string path;

public:
	const std::unordered_map<std::string, std::vector <double>> &getMap();
	void setTimeAndDateRead(SYSTEMTIME& time);
	void addElementToMap(std::string name, double price);
	const std::string & getTimeAndDateRead();
	void clearMap();

};
