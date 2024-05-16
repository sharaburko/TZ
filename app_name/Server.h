
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
	Logs logs{ time };

	SYSTEMTIME time;

	void createBars();
	void start();
	void stop();
	void read(Bar &bar);
	void write(Bar &bar);
	void addEventToLog(const std::string& message);
public:
	Server();
	~Server();

	void run();
};

