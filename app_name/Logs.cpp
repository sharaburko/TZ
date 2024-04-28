#include "Logs.h"

Logs::Logs(std::string path)
{
	this->path = std::filesystem::current_path().string() + "\\" + path;

	if(!std::filesystem::is_directory(path))
	{
		std::cout << "����� Logs �� �������\n";
		std::filesystem::create_directory(path);
		std::cout << "����� Logs �������\n";
	}
	else
	{
		std::cout << "����� Logs ����������\n";
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

void Logs::AddAnEvent(std::string event)
{
	write << event << "\n";
}
