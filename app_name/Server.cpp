#include "Server.h"

Server::Server()
{
	handle = CreateServer();
	std::cout << "Server created\n";
	StartServer(handle);
	std::cout << "Server is running\n";
}

Server::~Server()
{
	StopServer(handle);
	std::cout << "Server is stopped\n";
	DeleteServer(handle);
	std::cout << "Server deleted\n";
}

void* Server::getHandle()
{
	return handle;
}
