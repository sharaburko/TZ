
#pragma once

#include "Quotes.h"
#include <memory>
#include <fstream>
#include "Logs.h"
#include "Bar.h"
#include "Windows.h">
#include <string>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <mutex>
#include <thread>
#include <stdio.h>

class Server
{
private:
	void* handle;
	const int sizeBuffer = 2000;
	std::shared_ptr<char[]> buffer;
	bool isReadData = true;
	std::string tempBuffer;

	std::vector <Bar> bars;
	Logs logs{ time };

	SYSTEMTIME time;

	void createBars();
	void start();
	void stop();
	void read(Bar &bar);
	void write(Bar &bar);
	void addEventToLog(const std::string& message);
	void addElementToMapInBar(char* buffer, Bar& bar);
	std::string checkingBuffer(std::string bufferStream);

public:
	Server();
	~Server();
	void run();
	void stop_loop() { isReadData = false; }
};

