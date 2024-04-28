#pragma once
#include <string>
#include <iostream>

class Bar
{
private:
	std::string exchangeRates;
	std::string sign;
	std::string time;
	double price;
	int size;
	int month;
	int day;
	int year;
	int hour;
	int minute;

public:
	Bar();
	Bar(std::string exchangeRates, double price, int size, int month, int day, int year, int hour, int minute);
	void setMonth(int month);
	void setDay(int day);
	void setYear(int year);
	void setHour(int hour);
	void setMinute(int minute);
	void setExchangeRates(std::string exchangeRates);
	void setPrice(double price);

	int& getMonth();
	int& getDay();
	int& getYear();
	int& getHour();
	int& getMinute();
	std::string& getExchangeRates();
	double& getPrice();

	friend std::istream& operator >> (std::istream& stream, Bar &bar);
};
