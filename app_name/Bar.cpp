#include "Bar.h"

void Bar::setTimeAndDateRead(SYSTEMTIME& time)
{
	timeAndDateRead = std::to_string(time.wMonth) + "/" + std::to_string(time.wDay) + "/" +
		std::to_string(time.wYear) + " " + std::to_string(time.wHour) + ":" +
		std::to_string(time.wMinute);
}

const std::unordered_map<std::string, std::vector<double>> & Bar::getMap()
{
	return map;
}

void Bar::addElementToMap(std::string name, double price)
{
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

const std::string & Bar::getTimeAndDateRead()
{
	return timeAndDateRead;
}

void Bar::clearMap()
{
	map.clear();
}