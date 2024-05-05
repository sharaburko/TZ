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

void Server::addEventToLog(const std::string& message)
{
	logs.AddAnEvent(message, time);
}

void Server::read()
{
	std::stringstream stringBufer;
	std::string tempString;

	memset(buffer.get(), 0, sizeBuffer);

	int sizeData = ReadData(handle, buffer.get(), sizeBuffer);

	stringBufer << buffer.get();

	while(stringBufer >> tempString)
	{
		std::cmatch result;
		std::regex regular("(\\w{6})""(,{1})" "(\\w+)" "(,{1})" "([\\d\.]+)" "(,{1})" "(\\d+)");

		if(std::regex_match(tempString.c_str(), result, regular))
		{
			std::string name = result[1].str() + "_" + result[3].str();
			std::stringstream streamPrice(result[5]);
			double price;
			streamPrice >> price;

			if(map.contains(name))
			{
				map[name].push_back(price);
			}
			else
			{
				std::vector <double> temp;
				temp.push_back(price);
				map[name] = temp;
			}

			std::cout << name << " " << price << std::endl;				
		}

	}

	std::cout << '\n';

}

void Server::write()
{

	std::fstream write;

	for (const auto& [name, price] : map)
	{
		write.open("Bars//" + name + ".txt", std::ios::out | std::ios::app);
		double min = *std::min_element(begin(price), end(price));
		double max = *std::max_element(begin(price), end(price));
		write << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << ", "
			<< price.front() << " " << min << " " << max << " " << price.back();
		write.close();
	}

}
 
void Server::run()
{
	start();

	while (true)
	{
		GetLocalTime(&time);

		if(!time.wMinute % 2)
		{
			std::thread t1([&]() {
				read();
			});
			t1.detach();
		}
		else
		{
			std::thread t2([&]() {
				read();
			});
			t2.detach();
		}

		std::cout << std::this_thread::get_id << std::endl;			

		if (_kbhit())
		{

			//if (getch() == 3)  //Ctrl + C
			//{
			//	break;
			//}

			break;
		}

		
	}

	write();

	stop();
}