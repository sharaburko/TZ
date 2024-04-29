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
public:
	Logs();
	~Logs();
	void AddAnEvent(const std::string &event, SYSTEMTIME& time);
};

