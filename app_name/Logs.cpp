#include "Logs.h"

Logs::Logs()
{
	path = std::filesystem::current_path().string() + "\\" + "Logs";

	if(!std::filesystem::is_directory(path))
	{
		std::cout << "Папка Logs не найдена\n";
		std::filesystem::create_directory(path);
		std::cout << "Папка Logs создана\n";
	}
	else
	{
		std::cout << "Папка Logs существует\n";
	}

	write.open(path + "\\" + "Quotes.log" , std::ios::app | std::ios::out);

	if (!write.is_open())
	{
		std::cout << "Error. Opening error.\n";
	}
	else
	{
		write << "OK\n";
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

