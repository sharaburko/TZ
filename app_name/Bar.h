#pragma once
#include <string>

class Bar
{
private:
	std::string exchangeRates;
	double price;
	int month;
	int day;
	int year;
	int hour;
	int minute;
	int size;
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
};

