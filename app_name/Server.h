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
	std::mutex mtx;
	void* handle;
	const int sizeBuffer = 2000;
	std::shared_ptr<char[]> buffer;
	std::unordered_map<std::string, std::vector <double>> map;

	SYSTEMTIME time;

	Logs logs{time};
	Bar bar{logs, time};

	void start();
	void stop();
	void read();
	void write();

public:
	Server();
	~Server();

	void addEventToLog(const std::string&  message);
	void run();
};

