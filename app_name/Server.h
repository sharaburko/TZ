
#pragma once

#include "Quotes.h"
#include <memory>
#include <fstream>
#include "Logs.h"
#include "Bar.h"
#include "Windows.h">
#include <string>
#include <conio.h>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <mutex>
#include <thread>
 

class Server
{
private:
	void* handle;
	const int sizeBuffer = 2000;
	bool isReadData = 1;
	std::shared_ptr<char[]> buffer;
	std::unordered_map<std::string, std::vector <double>> map1;
	std::string timeAndDateRead;
	std::unordered_map<std::string, std::vector <double>> map2;
	//std::mutex mtx;

	SYSTEMTIME time;

	Logs logs{time};
	Bar bar{logs, time};

	void start();
	void stop();
	void read(std::unordered_map<std::string, std::vector <double>>& map);
	void write(std::unordered_map<std::string, std::vector <double>>& map);
	const std::string& getTimeAndDate();

public:
	Server();
	~Server();

	void addEventToLog(const std::string&  message);
	void run();
};

