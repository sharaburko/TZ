#include "Server.h"

Server::Server()
{
	handle = CreateServer();
	addEventToLog("Server created");
	buffer = std::shared_ptr<char[]>(new char[sizeBuffer]);
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

void Server::read()
{
	while (true)
	{
		GetLocalTime(&time);
		std::thread th;
		memset(buffer.get(), 0, sizeBuffer);

		int sizeData = ReadData(handle, buffer.get(), sizeBuffer);

		std::cout << buffer.get();

		if (_kbhit())
		{

			//if (getch() == 3)  //Ctrl + C
			//{
			//	break;
			//}

			break;
		}

	}
	std::cout << '\n';

}

void Server::run()
{
	start();
	read();
	stop();
}