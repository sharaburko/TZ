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
	constexpr  size_t countBars = 2;
	const std::string path = std::filesystem::current_path().string() + "\\" + "Bars";

	if (std::filesystem::is_directory(path)) {
		std::uintmax_t n{ std::filesystem::remove_all(path + "\\") };
		addEventToLog("Bars folder cleared");
	}

	std::filesystem::create_directory(path);
	addEventToLog("Bars folder create");

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

void Server::addElementToMapInBar(char *buffer, Bar& bar)
{
	std::stringstream stringStream;
	std::string strBuffer;

	stringStream << buffer;

	while (stringStream >> strBuffer)
	{
		std::cmatch result;
		std::regex regular("(\\w{6})""(,{1})" "(\\w+)" "(,{1})" "([\\d\.]+)" "(,{1})" "(\\d+)");

		if (std::regex_match(strBuffer.c_str(), result, regular))
		{
			std::string name = result[1].str() + "_" + result[3].str();

			std::stringstream priceStream(result[5]);
			double price;
			priceStream >> price;

			bar.addElementToMap(name, price);
		}
	}
}


void Server::read(Bar& bar)
{
	GetLocalTime(&time);
	bar.setTimeAndDateRead(time);
	int timeStartReading = time.wMinute;

	while (!(time.wMinute - timeStartReading)) {

		memset(buffer.get(), 0, sizeBuffer);
		ReadData(handle, buffer.get(), sizeBuffer);

		addElementToMapInBar(buffer.get(), bar);	


		if (_kbhit())
		{
			std::cout << _getch();
			//if(_getch() == )
			if (_getch() == 'a')  //Ctrl + C
			{				
				isReadData = false;
				break;
			}

			//isReadData = false;
			//break;
		}

		GetLocalTime(&time);
	}

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
	std::cout << "Press any key to stop reading...\n";

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
			std::thread t1([&]() {read(bars.back()); });

			if (!bars.front().getMap().empty()) {
				write(bars.front());
			}

			t1.join();
		}

		GetLocalTime(&time);
	}

	addEventToLog("Data reading is complete");

	for (auto & bar : bars)
	{
		if (!bar.getMap().empty()) {
			write(bar);
		}
	}

	stop();
}