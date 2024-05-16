
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
	std::shared_ptr<char[]> buffer;
	bool isReadData = 1;

	std::vector <Bar> bars;	
	//std::unordered_map<std::string, std::vector <double>> map1;
	//std::unordered_map<std::string, std::vector <double>> map2;
	//std::mutex mtx;

	SYSTEMTIME time;

	Logs logs{time};
	//Bar bar{logs, time};

	void createBars();
	void start();
	void stop();
	void read(Bar &bar);
	void write(Bar &bar);
	const std::string& getTimeAndDate();

public:
	Server();
	~Server();

	void addEventToLog(const std::string&  message);
	void run();
};

