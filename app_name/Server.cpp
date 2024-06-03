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
	stop();
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
	addEventToLog("Data reading stopped");

	for (auto& bar : bars)
	{
		if (!bar.getMap().empty()) {
			write(bar);
		}
	}

	StopServer(handle);
	addEventToLog("Server is stopped");
}

void Server::addEventToLog(const std::string& message)
{
	logs.AddAnEvent(message, time);
}

std::string Server::checkingBuffer(std::string bufferStream) {

	constexpr size_t positionCorrection = 1;

	if (!tempBuffer.empty())
	{
		bufferStream.insert(0, tempBuffer);
		tempBuffer.erase();
	}


	if (bufferStream.back() != '\n') {

		int lastTransfer = bufferStream.rfind('\n');

		tempBuffer += bufferStream.substr((lastTransfer + positionCorrection));
		bufferStream.erase(lastTransfer + positionCorrection);
	}

	return bufferStream;
}

void Server::addElementToMapInBar(char *buffer, Bar& bar)
{
	std::stringstream stringStream;
	std::string strBuffer;

	stringStream << checkingBuffer(buffer);

	while (stringStream >> strBuffer)
	{
		std::cmatch result;
		std::regex regular("(\\w+)""(,{1})" "(\\w+)" "(,{1})" "([\\d\.]+)" "(,{1})" "(\\d+)");

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

	while (!(time.wMinute - timeStartReading) && isReadData)
	{
		memset(buffer.get(), 0, sizeBuffer);
		ReadData(handle, buffer.get(), sizeBuffer);
		addElementToMapInBar(buffer.get(), bar);
		GetLocalTime(&time);
	}

}


void Server::write(Bar &bar)
{
	std::fstream write;

	for (const auto& [name, price] : bar.getMap())
	{
		write.open("Bars//" + name + ".csv", std::ios::out | std::ios::app);

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
	std::cout << "Press any key Ctrl + \"c\" to stop reading...\n";

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


}




