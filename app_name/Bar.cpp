#include "Bar.h"

void Bar::setMonth(int month)
{
	this->month = month;
}

void Bar::setDay(int day)
{
	this->day = day;
}

void Bar::setYear(int year)
{
	this->year = year;
}

void Bar::setHour(int hour)
{
	this->hour = hour;
}

void Bar::setMinute(int minute)
{
	this->minute = minute;
}

void Bar::setExchangeRates(std::string exchangeRates)
{
	this->exchangeRates = exchangeRates;
}

void Bar::setPrice(double price)
{
	this->price = price;
}


int& Bar::getMonth()
{
	return month;
}

int& Bar::getDay()
{
	return day;
}

int& Bar::getYear()
{
	return year;
}

int& Bar::getHour()
{
	return hour;
}

int& Bar::getMinute()
{
	return minute;
}

std::string& Bar::getExchangeRates()
{
	return exchangeRates;
}

double& Bar::getPrice()
{
	return price;
}



Bar::Bar()
{

}

Bar::Bar(std::string exchangeRates, double price, int size, int month, int day, int year, int hour, int minute)
{
	setMonth(month);
	setDay(day);
	setYear(year);
	setHour(hour);
	setMinute(minute);
	setExchangeRates(exchangeRates);
	setPrice(price);
}

std::istream& operator >> (std::istream& stream, Bar& bar) {
	std::string price;
	std::string size;
	std::getline(stream, bar.exchangeRates, ',');
	std::cout << bar.exchangeRates << " ";
	std::getline(stream, bar.sign, ',');
	std::cout << bar.sign << " ";
	std::getline(stream, price, ',');
	std::cout << price << " ";
	bar.price = std::stod(price);
	std::cout << bar.price << " ";
	std::getline(stream, size, '\n');
	std::cout << size << " ";
	bar.size = std::stod(size);
	std::cout << bar.size << "\n";

	return stream;
}