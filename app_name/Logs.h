#pragma once
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>

class Logs
{
private:
	std::string path;
	std::fstream write;
	std::string timeAndDate(SYSTEMTIME& time);
public:
	Logs(SYSTEMTIME& time);
	~Logs();
	void AddAnEvent(const std::string &event, SYSTEMTIME& time);
};

