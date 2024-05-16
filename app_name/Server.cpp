#include "Server.h"

Server::Server()
{
	handle = CreateServer();
	addEventToLog("Server created");
	buffer = std::shared_ptr<char[]>(new char[sizeBuffer]);

	createBars();
}

Server::~Server()
{
	DeleteServer(handle);
	addEventToLog("Server deleted");
}

void Server::createBars()
{
	const size_t countBars = 2;
	const std::string path = fs::current_path().string() + "\\" + "Bars";

	if (fs::is_directory(path)) {
		std::uintmax_t n{ fs::remove_all(path + "\\") };
		logs.AddAnEvent("Bars folder cleared", time);
	}

	fs::create_directory(path);
	logs.AddAnEvent("Bars folder create", time);

	bars.reserve(countBars);

	for (size_t i = 0; i < countBars; i++)
	{
		bars.emplace_back();
	}
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

void Server::read(Bar& bar)
{
	//mtx.lock();

	GetLocalTime(&time);
	bar.setTimeAndDateRead(time);

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

				bar.addElementToMap(name, price);
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

void Server::write(Bar &bar)
{
	std::fstream write;

	for (const auto& [name, price] : bar.getMap())
	{
		write.open("Bars//" + name + ".txt", std::ios::out | std::ios::app);

		double min = *std::min_element(begin(price), end(price));
		double max = *std::max_element(begin(price), end(price));

		write << bar.getTimeAndDateRead() << ", " << price.front() << " " << min << " " << max << " " << price.back() << "\n";
		
		write.close();
	}

	bar.clearMap();
}
 
void Server::run()
{
	start();
	GetLocalTime(&time);

	addEventToLog("Data reading started");

	while (isReadData)
	{

		if (time.wMinute % 2) {
			std::thread t1([&](){read(bars.front()); });

			if (!bars.back().getMap().empty()) {
				write(bars.back());
			}

			t1.join();
		}
		else
		{
			std::thread t1([&]() {bars.back(); });

			if (!bars.front().getMap().empty()) {
				write(bars.front());
			}

			t1.join();
		}

		GetLocalTime(&time);
	}

	addEventToLog("Data reading is complete. Loading...");

	for (auto & bar : bars)
	{
		if (!bar.getMap().empty()) {
			write(bar);
		}
	}

	stop();
}