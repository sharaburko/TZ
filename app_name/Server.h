#pragma once
#include "Quotes.h"
#include <memory>
#include <iostream>
#include "Logs.h"
#include "Bar.h"
#include "Windows.h">
#include <string>
#include <conio.h>

class Server
{
private:
	void* handle;
	const int sizeBuffer = 2000;
	std::shared_ptr<char[]> buffer;

	SYSTEMTIME time;

	Logs logs{time};
	Bar bar{logs, time};

	void start();
	void stop();
	void read();

public:
	void run();
	Server();
	~Server();
	const SYSTEMTIME & getTime();
	Logs& getLogs();
	void addEventToLog(const std::string&  message);
};

