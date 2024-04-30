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
	int sizeBuffer;
	char* buffer;
	SYSTEMTIME time;
	Logs logs;
	Bar bar;

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

