#pragma once
#include "Quotes.h"
#include <memory>
#include <iostream>
#include "Logs.h"
#include "Bar.h"
#include "Windows.h">
#include <string>

class Server
{
private:
	void* handle;
	const int sizeBuffer = 2000;
	std::shared_ptr<char[]> buffer;

	SYSTEMTIME time;

	Logs logs{time};
	Bar bar{logs, time};

public:
	Server();
	~Server();
	void start();
	void stop();
	void* getHandle();
	const SYSTEMTIME & getTime();
	Logs& getLogs();
	void addEventToLog(const std::string&  message);
};

