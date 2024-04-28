#pragma once
#include "Quotes.h"
#include <memory>
#include <iostream>

class Server
{
private:
	void* handle;
	int sizeBuffer;
	char* buffer;
public:
	Server();
	~Server();
	void* getHandle();
};

