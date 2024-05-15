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
	//mtx.lock();

	GetLocalTime(&time);
	int readingStartTime = time.wMinute;

	while (!(time.wMinute - readingStartTime)) {
		std::stringstream stringBuffer;
		std::string tempString;
		memset(buffer.get(), 0, sizeBuffer);
		int sizeData = ReadData(handle, buffer.get(), sizeBuffer);

		stringBuffer << buffer.get();

		while (stringBuffer >> tempString)
		{
			std::cmatch result;
			std::regex regular("(\\w{6})""(,{1})" "(\\w+)" "(,{1})" "([\\d\.]+)" "(,{1})" "(\\d+)");

			if (std::regex_match(tempString.c_str(), result, regular))
			{
				std::string name = result[1].str() + "_" + result[3].str();
				std::stringstream streamPrice(result[5]);
				double price;
				streamPrice >> price;

				if (map.contains(name))
				{
					map[name].push_back(price);
				}
				else
				{
					std::vector <double> temp;
					temp.push_back(price);
					map[name] = temp;
				}

			}			

		}

		if (_kbhit())
		{
			//if (_getch() == 3)  //Ctrl + C
			//{
			//	break;
			//	isReadData = false;
			//}
			
			isReadData = false;
			break;
		}

		GetLocalTime(&time);
	}

	//mtx.unlock();
}

void Server::write(std::unordered_map<std::string, std::vector <double>>& map)
{
	std::fstream write;

	for (const auto& [name, price] : map)
	{
		write.open("Bars//" + name + ".txt", std::ios::out | std::ios::app);
		double min = *std::min_element(begin(price), end(price));
		double max = *std::max_element(begin(price), end(price));
		std::string dateAndTime = std::to_string(time.wMonth) + "/" + std::to_string(time.wDay) + "/" +
			std::to_string(time.wYear) + " " + std::to_string(time.wHour) + ":" +
			std::to_string(time.wMinute);

		write << dateAndTime << ", " << price.front() << " " << min << " " << max << " " << price.back() << "\n";
		write.close();
	}
	map.clear();
}
 
void Server::run()
{
	start();
	GetLocalTime(&time);

	addEventToLog("Data reading started");

	while (isReadData)
	{

		if (time.wMinute % 2) {
			std::thread t1([&](){read(map1);	});
			if (!map2.empty()) write(map2);
			t1.join();
		}
		else
		{
			std::thread t1([&]() {read(map2); });
			if (!map1.empty()) write(map1);
			t1.join();
		}

		GetLocalTime(&time);
	}

	addEventToLog("Data reading is complete. Loading...");
	if(!map1.empty()) write(map1);
	if(!map2.empty()) write(map2);

	stop();
}