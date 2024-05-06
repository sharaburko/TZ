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

const std::string& Server::getTimeAndDate()
{
	return std::to_string(time.wMonth) + "/" + std::to_string(time.wDay) + "/" + 
		   std::to_string(time.wYear) + " " + std::to_string(time.wHour) + ":" + 
		   std::to_string(time.wMinute);
}

void Server::read(std::unordered_map<std::string, std::vector <double>>& map)
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

			std::cout << getTimeAndDate() << name << " " << price << std::endl;
		}

	}

	std::cout << '\n';

}

void Server::write(std::unordered_map<std::string, std::vector <double>>& map)
{

	std::fstream write;

	for (const auto& [name, price] : map)
	{
		write.open("Bars//" + name + ".txt", std::ios::out | std::ios::app);
		double min = *std::min_element(begin(price), end(price));
		double max = *std::max_element(begin(price), end(price));
		write << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << ", "
			<< price.front() << " " << min << " " << max << " " << price.back() << "\n";
		write.close();
	}
	map.clear();

}
 
void Server::run()
{
	start();

	while (true)
	{
		GetLocalTime(&time);

		std::thread t1([&]() {

			while(!time.wMinute % 2)
			{
				GetLocalTime(&time);

				read(map1);
			}

		});

		write(map2);

		t1.join();

		std::thread t2([&]() {

			while (time.wMinute % 2)
			{
				GetLocalTime(&time);

				read(map2);
			}

		});

		write(map1);
		t2.join();


		if (_kbhit())
		{

			//if (getch() == 3)  //Ctrl + C
			//{
			//	break;
			//}

			break;
		}

		
	}

	stop();
}