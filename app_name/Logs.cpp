#include "Logs.h"

Logs::Logs(SYSTEMTIME& time)
{
	path = std::filesystem::current_path().string() + "\\" + "Logs";
	GetLocalTime(&time);
	std::string timeAndDateCreate = std::to_string(time.wDay) + "/" + std::to_string(time.wMonth) + "/" +
									std::to_string(time.wYear) + " " + std::to_string(time.wHour) + ":" +
									std::to_string(time.wMinute);

	if(!std::filesystem::is_directory(path))
	{
		std::filesystem::create_directory(path);
		std::cout << timeAndDateCreate << " " << "Logs folder created\n";
	}
	else
	{
		std::cout << timeAndDateCreate << " " << "Logs folder found\n";
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

void Logs::AddAnEvent(const std::string &event, SYSTEMTIME &time)
{
	GetLocalTime(&time);

	std::string timeAndDateAddEvent = std::to_string(time.wDay) + "/" + std::to_string(time.wMonth) + "/" +
									  std::to_string(time.wYear) + " " + std::to_string(time.wHour) + ":" +
									  std::to_string(time.wMinute);

	write << timeAndDateAddEvent << " " << event << "\n";
	std::cout << timeAndDateAddEvent << " " << event << "\n";
}

