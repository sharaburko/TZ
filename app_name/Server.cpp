#include "Server.h"

Server::Server()
{
	handle = CreateServer();
	addEventToLog("Server created");
}

Server::~Server()
{
	DeleteServer(handle);
	addEventToLog("Server deleted");
}

void Server::start()
{
	StartServer(handle);
	addEventToLog("Server is running");
}

void Server::stop()
{
	StopServer(handle);
	addEventToLog("Server is stopped");
}

void* Server::getHandle()
{
	return handle;
}

const SYSTEMTIME& Server::getTime()
{
	return time;
}

Logs& Server::getLogs()
{
	return logs;
}

void Server::addEventToLog(const std::string& message)
{
	logs.AddAnEvent(message, time);
}
