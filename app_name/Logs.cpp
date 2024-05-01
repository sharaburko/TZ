#include "Logs.h"

Logs::Logs(SYSTEMTIME& time)
{
	path = std::filesystem::current_path().string() + "\\" + "Logs";
	GetLocalTime(&time);

	if(!std::filesystem::is_directory(path))
	{
		std::filesystem::create_directory(path);
		std::cout << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << " ";
		std::cout << "Logs folder created\n";
	}
	else
	{
		std::cout << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << " ";
		std::cout << "Logs folder found\n";
	}

	write.open(path + "\\" + "Quotes.log" , std::ios::app | std::ios::out);

	if (!write.is_open())
	{
		std::cout << "Error. Opening error.\n";
	}

}

Logs::~Logs()
{
	write.close();
}

void Logs::AddAnEvent(const std::string &event, SYSTEMTIME &time)
{
	GetLocalTime(&time);
	write << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << " ";
	write << event << "\n";
	std::cout << time.wMonth << "/" << time.wDay << "/" << time.wYear << " " << time.wHour << ":" << time.wMinute << " ";
	std::cout << event << "\n";
}

