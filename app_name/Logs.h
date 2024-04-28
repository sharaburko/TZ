#pragma once
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

class Logs
{
private:
	std::string path;
	std::fstream write;
public:
	Logs(std::string path);
	~Logs();
	void AddAnEvent(std::string event);
};

