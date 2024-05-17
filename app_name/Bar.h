#pragma once
#include <string>
#include <Windows.h>
#include <filesystem>
#include <unordered_map>

class Bar
{
private:
	std::unordered_map<std::string, std::vector <double>> map;
	std::string timeAndDateRead;

public:
	const std::unordered_map<std::string, std::vector <double>> &getMap();
	const std::string& getTimeAndDateRead();

	void setTimeAndDateRead(SYSTEMTIME& time);
	void addElementToMap(std::string &name, double &price);
	void clearMap();
};
