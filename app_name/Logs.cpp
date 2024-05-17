#include "Logs.h"

Logs::Logs(SYSTEMTIME& time)
{
	path = std::filesystem::current_path().string() + "\\" + "Logs";
	GetLocalTime(&time);

	if(!std::filesystem::is_directory(path))
	{
		std::filesystem::create_directory(path);
		std::cout << timeAndDate(time) << " " << "Logs folder created\n";
	}
	else
	{
		std::cout << timeAndDate(time) << " " << "Logs folder found\n";
	}

	write.open(path + "\\" + "Quotes.log" , std::ios::app | std::ios::out);

	if (!write.is_open())
	{
		std::cout << "Error. Opening error.\n";
		exit(1);
	}

}

Logs::~Logs()
{
	write.close();
}

std::string Logs::timeAndDate(SYSTEMTIME& time)
{
	return std::to_string(time.wDay) + "/" + std::to_string(time.wMonth) + "/" +
		   std::to_string(time.wYear) + " " + std::to_string(time.wHour) + ":" +
		   std::to_string(time.wMinute);
}

void Logs::AddAnEvent(const std::string &event, SYSTEMTIME &time)
{
	GetLocalTime(&time);

	write << timeAndDate(time) << " " << event << "\n";
	std::cout << timeAndDate(time) << " " << event << "\n";
}

